/*ͼ�����Ĥ������filter2D
*/

#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;//�������ռ�
using namespace std;
int main(int argc, char** argv) {
	Mat src, dst1;
	src = imread("F:/OutPutResult/Test/Test/dolam.jpg");//��ȡһ��ͼƬ
	if (!src.data) {
		cout<<"could not load image..."<<endl;
		return -1;
	}
	imshow("input_image", src);
	Mat dst2;
	cvtColor(src, dst1, CV_BGR2GRAY);
	dst1.copyTo(dst2);
	//GRAY
	for (int row = 1; row < dst1.rows - 1; row++) {
		for (int col = 1; col < dst1.cols - 1; col++) {
			dst2.at<uchar>(row, col) = saturate_cast<uchar>(5 * dst1.at<uchar>(row, col) - dst1.at<uchar>(row - 1, col) - dst1.at<uchar>(row + 1, col)
				-dst1.at<uchar>(row,col-1)-dst1.at<uchar>(row,col+1)
				);
		}
	}
	imshow("dst2", dst2);
	//BGR
	Mat dst3;
	dst3 = Mat::zeros(src.size(), src.type());//����һ����Դͼ���С���������ͬ��ȫ0����
	int cols = (src.cols - 1)*src.channels();//��ȡͼ�������,һ����Ҫ����ͼ���ͨ����
	int rows = src.rows;//��ȡͼ�������
	int offsetx = src.channels();
	for (int row = 1; row < rows - 1; row++) {
		const uchar*  previous =src.ptr<uchar>(row - 1);
		const uchar*  current = src.ptr<uchar>(row);
		const uchar*  next = src.ptr<uchar>(row + 1);
		uchar*  output = dst3.ptr<uchar>(row);
		for (int col = offsetx; col < cols; col++) {
			output[col] = saturate_cast<uchar>(5 * current[col] - previous[col] - next[col] - current[col - 1] - current[col + 1]);
		}
	}
	imshow("dst3", dst3);
	Mat dst4;
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(src, dst4, src.depth(), kernel);
	imshow("dst4", dst4);
	waitKey(0);
	return 0;
}
