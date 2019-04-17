#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <ctime>
using namespace cv;
using namespace std;

//��ֵ�˲�
void MeanFiltering(const Mat &src, Mat &dst) {
	if (!src.data) return;
	//at�������ص�
	for (int i = 1; i<src.rows; ++i)
		for (int j = 1; j < src.cols; ++j) {
			if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1)<src.rows && (j + 1)<src.cols) {//��Ե�����д���
				dst.at<Vec3b>(i, j)[0] = (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i - 1, j - 1)[0] + src.at<Vec3b>(i - 1, j)[0] + src.at<Vec3b>(i, j - 1)[0] +
					src.at<Vec3b>(i - 1, j + 1)[0] + src.at<Vec3b>(i + 1, j - 1)[0] + src.at<Vec3b>(i + 1, j + 1)[0] + src.at<Vec3b>(i, j + 1)[0] +
					src.at<Vec3b>(i + 1, j)[0]) / 9;
				dst.at<Vec3b>(i, j)[1] = (src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i - 1, j - 1)[1] + src.at<Vec3b>(i - 1, j)[1] + src.at<Vec3b>(i, j - 1)[1] +
					src.at<Vec3b>(i - 1, j + 1)[1] + src.at<Vec3b>(i + 1, j - 1)[1] + src.at<Vec3b>(i + 1, j + 1)[1] + src.at<Vec3b>(i, j + 1)[1] +
					src.at<Vec3b>(i + 1, j)[1]) / 9;
				dst.at<Vec3b>(i, j)[2] = (src.at<Vec3b>(i, j)[2] + src.at<Vec3b>(i - 1, j - 1)[2] + src.at<Vec3b>(i - 1, j)[2] + src.at<Vec3b>(i, j - 1)[2] +
					src.at<Vec3b>(i - 1, j + 1)[2] + src.at<Vec3b>(i + 1, j - 1)[2] + src.at<Vec3b>(i + 1, j + 1)[2] + src.at<Vec3b>(i, j + 1)[2] +
					src.at<Vec3b>(i + 1, j)[2]) / 9;
			}
			else {//��Ե��ֵ
				dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0];
				dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1];
				dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2];
			}
		}
}
//ͼ���λ�
void salt(Mat &image, int num) {
	if (!image.data) return;//��ֹ�����ͼ
	int i, j;
	srand(time(NULL));
	for (int x = 0; x < num; ++x) {
		i = rand() % image.rows;
		j = rand() % image.cols;
		image.at<Vec3b>(i, j)[0] = 255;
		image.at<Vec3b>(i, j)[1] = 255;
		image.at<Vec3b>(i, j)[2] = 255;
	}
}
void main() {
	Mat image = cv::imread("C:\\Users\\cccccc\\Desktop\\��ͨ.jpg");

	Mat Salt_Image;
	image.copyTo(Salt_Image);
	salt(Salt_Image, 3000);

	Mat image1(image.size(), image.type());
	Mat image2;
	MeanFiltering(Salt_Image, image1);
	blur(Salt_Image, image2, Size(3, 3));//openCV���Դ��ľ�ֵ�˲�����
	imshow("ԭͼ", image);
	imshow("�Զ����ֵ�˲�", image1);
	imshow("openCV�Դ��ľ�ֵ�˲�", image2);
	/*Mat dst0;                                        //ͼ������
	resize(image,dst0, Size(), 1,2);
	imshow("����",dst0);*/
	waitKey();
}
