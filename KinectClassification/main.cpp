#include <iostream>

#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\dnn.hpp>
#include "windows.h"
#include "NuiApi.h"

using namespace std;
using namespace cv;

#define COLOR_WIDTH					640  
#define COLOR_HIGHT					480  
#define DEPTH_WIDTH					640  
#define DEPTH_HIGHT					480  
#define SKELETON_WIDTH				640  
#define SKELETON_HIGHT				480  
#define CHANNEL                     3  
#define WIDTH						80
#define HEIGHT						40

HANDLE       m_hNextVideoFrameEvent;
HANDLE       m_hNextDepthFrameEvent;
HANDLE       m_hNextSkeletonEvent;
HANDLE       m_pVideoStreamHandle;
HANDLE       m_pDepthStreamHandle;
HANDLE       m_hEvNuiProcessStop;


//---Image stream resolution-------------------------------
NUI_IMAGE_RESOLUTION colorResolution = NUI_IMAGE_RESOLUTION_640x480;	//set image resolution
NUI_IMAGE_RESOLUTION depthResolution = NUI_IMAGE_RESOLUTION_640x480;

//---show images------------------------------------------
Mat depthRGB(DEPTH_HIGHT, DEPTH_WIDTH, CV_8UC3, Scalar(0, 0, 0));
Mat colorRGB(COLOR_HIGHT, COLOR_WIDTH, CV_8UC3, Scalar(0, 0, 0));
//---color definition------------------------------
const Scalar SKELETON_COLORS[NUI_SKELETON_COUNT] =
{
	//Scalar(0, 0, 255),      // Blue
	Scalar(255, 255, 255), Scalar(255, 255, 255),Scalar(255, 255, 255),Scalar(255, 255, 255)   // white
	//Scalar(0, 255, 0),      // Green
	//Scalar(255, 255, 64),   // Yellow
	//Scalar(64, 255, 255),   // Light blue
	//Scalar(255, 64, 255),   // Purple
	//Scalar(255, 128, 128)   // Pink
};
cv::dnn::Net model = cv::dnn::readNetFromONNX("model.onnx"); 

int classification(cv::dnn::Net model, cv::Mat& frame) {
	cv::Mat image;
	cv::resize(frame, image, cv::Size(224, 224));// Resize image to 224x224
	image.convertTo(image, CV_32F); // Convert pixel values into float
	int sz[] = { 1, 224,224, 3 }; // input shape
	cv::Mat input(4, sz, CV_32F, image.data); // create input
	image = image / 255.; // Normalize image
	model.setInput(input); 
	cv::Mat outputs = model.forward(); // Get prediction output from model

	cv::Point classIdPoint;
	double final_prob;
	minMaxLoc(outputs, 0, &final_prob, 0, &classIdPoint); // get classification from max probability
	int label_id = classIdPoint.x; // get label
	return label_id;
}

//turn depth image into RGB information and show body region
HRESULT DepthToRGB(USHORT depth, uchar& red, uchar& green, uchar& blue)
{
	SHORT realDepth = NuiDepthPixelToDepth(depth);
	USHORT playerIndex = NuiDepthPixelToPlayerIndex(depth);//get depth information of player;
	// Convert depth info into an intensity for display
	BYTE b = 255 - static_cast<BYTE>(256 * realDepth / 0x0fff);
	switch (playerIndex)
	{
		//no person in the scene£¬only gray background, color:[0,128];
	case 0:
		red = b / 2;
		green = b / 2;
		blue = b / 2;
		break;

	case 1:
		red = b;
		green = 0;
		blue = 0;
		break;

	case 2:
		red = 0;
		green = b;
		blue = 0;
		break;

	case 3:
		red = b / 4;
		green = b;
		blue = b;
		break;

	case 4:
		red = b;
		green = b;
		blue = b / 4;
		break;

	case 5:
		red = b;
		green = b / 4;
		blue = b;
		break;

	case 6:
		red = b / 2;
		green = b / 2;
		blue = b;
		break;

	case 7:
		red = 255 - b / 2;
		green = 255 - b / 2;
		blue = 255 - b / 2;
		break;

	default:
		red = 0;
		green = 0;
		blue = 0;
		break;

	}
	return S_OK;
}



//get RGB image and show
int DrawColor(HANDLE h)
{
	const NUI_IMAGE_FRAME* pImageFrame = NULL;
	HRESULT hr = NuiImageStreamGetNextFrame(h, 0, &pImageFrame);
	if (FAILED(hr))
	{
		cout << "GetColor Image Frame Failed" << endl;
		return-1;
	}
	INuiFrameTexture* pTexture = pImageFrame->pFrameTexture;
	NUI_LOCKED_RECT LockedRect;
	pTexture->LockRect(0, &LockedRect, NULL, 0);
	if (LockedRect.Pitch != 0)
	{
		BYTE* pBuffer = (BYTE*)LockedRect.pBits;
		//OpenCV show video
		if (true)
		{
			//colorRGB.setTo(0);
			Mat temp(COLOR_HIGHT, COLOR_WIDTH, CV_8UC4, pBuffer);// get frame
			Mat temp2;
			cv::cvtColor(temp, temp2, cv::COLOR_BGR2RGB);// convert frame color
			int pred = classification(model, temp2); // classification
			std::string out_text = cv::format("Pose %d", pred + 1);
			// put the class name text on top of the image
			cv::putText(temp, out_text, cv::Point(25, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
			//colorRGB = temp;
			cv::imshow("Classification", temp); // show image
		}
		int c = waitKey(1);//Press Esc to end 
		//Press Esc, q or Q to end
		if (c == 27 || c == 'q' || c == 'Q')
		{
			SetEvent(m_hEvNuiProcessStop);
		}
	}
	NuiImageStreamReleaseFrame(h, pImageFrame);
	return 0;
}


//get depth image and show
int DrawDepth(HANDLE h)
{
	const NUI_IMAGE_FRAME* pImageFrame = NULL;
	HRESULT hr = NuiImageStreamGetNextFrame(h, 0, &pImageFrame);
	if (FAILED(hr))
	{
		cout << "GetDepth Image Frame Failed" << endl;
		return-1;
	}
	INuiFrameTexture* pTexture = pImageFrame->pFrameTexture;
	NUI_LOCKED_RECT LockedRect;
	pTexture->LockRect(0, &LockedRect, NULL, 0);
	if (LockedRect.Pitch != 0)
	{
		BYTE* pBuff = (BYTE*)LockedRect.pBits;
		//OpenCV show depth video
		if (true)
		{
			Mat depthTmp(DEPTH_HIGHT, DEPTH_WIDTH, CV_16U, pBuff);
			//imshow("Depth",depthTmp);

			depthRGB.setTo(0);

			//show skeleton
			for (int y = 0; y < DEPTH_HIGHT; y++)
			{
				const USHORT* p_depthTmp = depthTmp.ptr<USHORT>(y);
				uchar* p_depthRGB = depthRGB.ptr<uchar>(y);
				for (int x = 0; x < DEPTH_WIDTH; x++)
				{
					USHORT depthValue = p_depthTmp[x];
					if (depthValue != 63355)
					{
						uchar redValue, greenValue, blueValue;
						DepthToRGB(depthValue, redValue, greenValue, blueValue);
						p_depthRGB[3 * x] = blueValue;
						p_depthRGB[3 * x + 1] = greenValue;
						p_depthRGB[3 * x + 2] = redValue;
					}
					else
					{
						p_depthRGB[3 * x] = 0;
						p_depthRGB[3 * x + 1] = 0;
						p_depthRGB[3 * x + 2] = 0;
					}

				}
			}
			//imshow("DepthRGB",depthRGB);


		}
		int c = waitKey(1);//Press Esc to end 
		//Press Esc, q or Q to end
		if (c == 27 || c == 'q' || c == 'Q')
		{
			SetEvent(m_hEvNuiProcessStop);
		}
	}
	NuiImageStreamReleaseFrame(h, pImageFrame);
	return 0;
}


//get skeleton and show
int DrawSkeleton()
{
	NUI_SKELETON_FRAME SkeletonFrame;
	cv::Point pt[20];
	HRESULT hr = NuiSkeletonGetNextFrame(0, &SkeletonFrame);
	if (FAILED(hr))
	{
		cout << "GetSkeleton Image Frame Failed" << endl;
		return -1;
	}

	bool bFoundSkeleton = false;
	for (int i = 0; i < NUI_SKELETON_COUNT; i++)
	{
		if (SkeletonFrame.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
		{
			bFoundSkeleton = true;
		}
	}
	//Has skeletons!  
	if (bFoundSkeleton)
	{
		NuiTransformSmooth(&SkeletonFrame, NULL);
		//cout<<"skeleton num:"<<NUI_SKELETON_COUNT<<endl;
		for (int i = 0; i < NUI_SKELETON_COUNT; i++)
		{
			NUI_SKELETON_TRACKING_STATE trackingState = SkeletonFrame.SkeletonData[i].eTrackingState;
			if (trackingState == NUI_SKELETON_TRACKED)  //tracking skeleton position;
			{
				//NUI_SKELETON_DATA *pSkel = &(SkeletonFrame.SkeletonData[i]);
				NUI_SKELETON_DATA  SkelData = SkeletonFrame.SkeletonData[i];
				Point jointPositions[NUI_SKELETON_POSITION_COUNT];

				for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; ++j)
				{
					LONG x, y;

					USHORT depth;
					//cout << j << " :(" << SkelData.SkeletonPositions[j].x << "," << SkelData.SkeletonPositions[j].y << ") ";
					NuiTransformSkeletonToDepthImage(SkelData.SkeletonPositions[j], &x, &y, &depth, depthResolution);

					//circle(depthRGB, Point(x,y), 5, Scalar(255,255,255), -1, CV_AA);
					jointPositions[j] = Point(x, y);
				}

				for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; ++j)
				{
					if (SkelData.eSkeletonPositionTrackingState[j] == NUI_SKELETON_POSITION_TRACKED)
					{
						circle(colorRGB, jointPositions[j], 5, SKELETON_COLORS[i], -1, LINE_AA);
						circle(colorRGB, jointPositions[j], 6, Scalar(0, 0, 0), 1, LINE_AA);
					}
					else if (SkelData.eSkeletonPositionTrackingState[j] == NUI_SKELETON_POSITION_INFERRED)
					{
						circle(colorRGB, jointPositions[j], 5, Scalar(255, 255, 255), -1, LINE_AA);
					}

				}
				//cout << endl;
			}
			else if (trackingState == NUI_SKELETON_POSITION_INFERRED) //predict skeleton position
			{
				LONG x, y;
				USHORT depth = 0;
				NuiTransformSkeletonToDepthImage(SkeletonFrame.SkeletonData[i].Position, &x, &y, &depth, depthResolution);
				//cout << SkeletonFrame.SkeletonData[i].Position.x << ";" << SkeletonFrame.SkeletonData[i].Position.y << endl;
				circle(colorRGB, Point(x, y), 7, CV_RGB(0, 0, 0), cv::FILLED);
			}

		}

	}
	imshow("SkeletonDepth", colorRGB);
	int c = waitKey(1);//Press Esc to end 
	//Press Esc, q or Q to end
	if (c == 27 || c == 'q' || c == 'Q')
	{
		SetEvent(m_hEvNuiProcessStop);
	}
	return 0;
}


//kinect get data
DWORD WINAPI KinectDataThread(LPVOID pParam)
{
	HANDLE hEvents[4] = { m_hEvNuiProcessStop,m_hNextVideoFrameEvent,
		m_hNextDepthFrameEvent,m_hNextSkeletonEvent };
	while (1)
	{
		int nEventIdx;
		nEventIdx = WaitForMultipleObjects(sizeof(hEvents) / sizeof(hEvents[0]),
			hEvents, FALSE, 100);
		if (WAIT_OBJECT_0 == WaitForSingleObject(m_hEvNuiProcessStop, 0))
		{
			break;
		}
		//Process signal events  
		if (WAIT_OBJECT_0 == WaitForSingleObject(m_hNextVideoFrameEvent, 0))
		{
			DrawColor(m_pVideoStreamHandle);
		}
		/*
		if (WAIT_OBJECT_0 == WaitForSingleObject(m_hNextDepthFrameEvent, 0))
		{
			DrawDepth(m_pDepthStreamHandle);
		}*/
		/*
		if (WAIT_OBJECT_0 == WaitForSingleObject(m_hNextSkeletonEvent, 0))
		{
			DrawSkeleton();
		}*/

	}
	CloseHandle(m_hEvNuiProcessStop);
	m_hEvNuiProcessStop = NULL;
	CloseHandle(m_hNextSkeletonEvent);
	CloseHandle(m_hNextDepthFrameEvent);
	CloseHandle(m_hNextVideoFrameEvent);
	return 0;
}


int main(int argc, char* argv[])
{

	//initialize NUI  
	HRESULT hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_SKELETON);
	if (hr != S_OK)
	{
		cout << "Nui Initialize Failed" << endl;
		return hr;
	}


	//open KINECT device to get RGB frame
	m_hNextVideoFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_pVideoStreamHandle = NULL;
	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, colorResolution, 0,
		2, m_hNextVideoFrameEvent, &m_pVideoStreamHandle);
	if (FAILED(hr))
	{
		cout << "Could not open image stream video" << endl;
		return hr;
	}
	m_hNextDepthFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_pDepthStreamHandle = NULL;
	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, depthResolution, 0,
		2, m_hNextDepthFrameEvent, &m_pDepthStreamHandle);
	if (FAILED(hr))
	{
		cout << "Could not open depth stream video" << endl;
		return hr;
	}
	m_hNextSkeletonEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//set tracking skeleton event flage£º 
	//seat flag|NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT;only 10 points: head and arms£»
	//stand flag&~(NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT);20 points£»
	hr = NuiSkeletonTrackingEnable(m_hNextSkeletonEvent,
		NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT
		/*NUI_SKELETON_TRACKING_FLAG_ENABLE_IN_NEAR_RANGE*//*&(~NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT)*/);
	if (FAILED(hr))
	{
		cout << "Could not open skeleton stream video" << endl;
		return hr;
	}
	m_hEvNuiProcessStop = CreateEvent(NULL, TRUE, FALSE, NULL);//end event£»

	//start multi process---for RGB, depth and skeleton£»  
	HANDLE m_hProcesss = CreateThread(NULL, 0, KinectDataThread, 0, 0, 0);
	///  

	while (m_hEvNuiProcessStop != NULL)
	{
		WaitForSingleObject(m_hProcesss, INFINITE);
		CloseHandle(m_hProcesss);
		m_hProcesss = NULL;
	}

	//Clean up.  
	NuiShutdown();
	return 0;
}

