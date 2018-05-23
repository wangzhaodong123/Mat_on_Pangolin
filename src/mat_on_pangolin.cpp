/*
 * 
 * 将cv::Mat类型图像在pangolin界面上显示
 * 
 */

#include <iostream>
#include <boost/iterator/iterator_concepts.hpp>

#include <pangolin/pangolin.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace pangolin;
using namespace cv;


//将cv::mat类型数据转化成pangolin的unsigned char型数组
void setImageData(unsigned char * imageArray, cv::Mat image)
{
  //确定行数和列数
  int clos = image.cols;
  int rows = image.rows;
  
  //将每个像素的每个通道的值按照一维数组的形式放入imageArray
  int imageArray_count=0;
  for ( int i=0;i<rows;i++ )
  {
    for ( int j=0;j<clos;j++ )
    {
      imageArray[imageArray_count] = (unsigned char)image.at<Vec3b>(i,j)[0];
      imageArray_count++;
      imageArray[imageArray_count] = (unsigned char)image.at<Vec3b>(i,j)[1];
      imageArray_count++;
      imageArray[imageArray_count] = (unsigned char)image.at<Vec3b>(i,j)[2];
      imageArray_count++;
    }
  }
}


//主函数
int main( int argc, char** argv )
{
  //输入参数校验
  if ( argc != 2 )
  {
    cerr<<" Usage: "<<argv[0]<<" image !"<<endl;
  }
  
  //从参数中读取图像
  Mat image_initial = imread( argv[1], 6 );
  if ( image_initial.data == nullptr )
  { 
    cerr<<" Image read failed ! "<<endl;
    return 1;
  }
  
  //获得图像长和宽
  int width =  image_initial.cols;
  int height = image_initial.rows;
  
  //定义opencv窗口
  namedWindow("opencv",1);
  
  //定义pangolin窗口的名称，大小
  pangolin::CreateWindowAndBind("Pangolin",width,height);

  // 3D Mouse handler requires depth testing to be enabled
  glEnable(GL_DEPTH_TEST);

  // Issue specific OpenGl we might need
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
 
  //图像显示“窗口”，位置与按键栏紧邻，大小640*480
  pangolin::View& d_image = pangolin::Display("image")
      .SetBounds(1,0,1,0)
      .SetLock(pangolin::LockRight, pangolin::LockBottom);

  //pangolin的输入图像数组
  unsigned char* imageArray = new unsigned char[3*width*height];
  // ？？？
  pangolin::GlTexture imageTexture(width,height);
  
  //循环显示
  while(!pangolin::ShouldQuit())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //这一大堆我也不知道什么意思，反正都不能缺
    //Set some random image data and upload to GPU
    //将cv::mat类型转化成pangolin的关键函数
    setImageData(imageArray,image_initial);
    imageTexture.Upload(imageArray,GL_RGB,GL_UNSIGNED_BYTE);
    d_image.Activate();
    
    //设置图片显示的色调好像是
    glColor3f(1.0,1.0,1.0);
    
    //这里有好几个将图像翻转和镜像显示的函数
    imageTexture.RenderToViewportFlipY();

    pangolin::FinishFrame();
    
    //更新opencv窗口
    imshow("opencv",image_initial);
    waitKey(1);
    
    //当按下Esc键时退出大循环
    char c = (char)waitKey(10);  
    if( c == 27 )  
      break;
  }	  
    
  
  destroyWindow("opencv");
  delete[] imageArray;
  //
  return 0;
}