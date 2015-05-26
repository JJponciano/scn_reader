/**
*  @copyright 2015 Jean-Jacques PONCIANO, Claire PRUDHOMME
* All rights reserved.
* This file is part of scn reader.
*
* scn reader is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* scn reader is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>
* @author Jean-Jacques PONCIANO and Claire PRUDHOMME
* Contact: ponciano.jeanjacques@gmail.com
* @version 0.1
*/
#include "Point.h"

PointGL::PointGL() {
    rad=(float)3.14159265/(float)180.0;
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->epsilon=1000;
}

PointGL::PointGL(float x, float y,float z) {
    rad=(float)3.14159265/(float)180.0;
    this->x = x;
    this->y = y;
    this->z = z;
    this->epsilon=1000;
}

PointGL::PointGL(const PointGL& orig) {
    rad=(float)3.14159265/(float)180.0;
    this->x = orig.x;
    this->y = orig.y;
    this->z = orig.z;
    this->epsilon=1000;
}
float PointGL::truncation(int trunc, float f){
    int ftrunc=(int)(f*trunc);
    float f2=((float)ftrunc)/((float)trunc);
            return f2;
}
int PointGL::getEpsilon() const
{
    return epsilon;
}

void PointGL::setEpsilon(int value)
{
    if(value%10==0&&value>0)
    epsilon = value;
}


bool PointGL::operator==(const PointGL &a)
{
    //rounded to the thousandth
    int roundX=this->x*epsilon ;
    int roundY=this->y*epsilon ;
    int roundZ=this->z*epsilon ;

    int aX=a.getX()*epsilon ;
    int aY=a.getY()*epsilon ;
    int aZ=a.getZ()*epsilon ;

    return roundX== aX&&roundY== aY &&roundZ== aZ;

}

bool PointGL::operator!=(const PointGL &a)
{
    //rounded to the thousandth
    int roundX=this->x*epsilon ;
    int roundY=this->y*epsilon ;
    int roundZ=this->z*epsilon ;

    int aX=a.getX()*epsilon ;
    int aY=a.getY()*epsilon ;
    int aZ=a.getZ()*epsilon ;

    return roundX!= aX||roundY!= aY ||roundZ!= aZ;
}

void PointGL::operator-(const PointGL &a)
{
    this->x-=a.getX();
    this->y-=a.getY();
    this->z-=a.getZ();
}

bool PointGL::distanceX(const PointGL point,float distance)const
{
    if(distance<0.0)
        distance=-1.0*distance;
        //get distance between p1 and p2 - average spacing between 2 tracks
        float x1=this->getX();
        float x2=point.getX();
        float pv=x1-x2;
        if(pv<0.0)
            pv=-1.0*pv;
        return pv<distance;
}
bool PointGL::distanceY(const PointGL point,float distance)const
{
    if(distance<0.0)
        distance=-1.0*distance;
        //get distance between p1 and p2 - average spacing between 2 tracks
        float y1=this->getY();
        float y2=point.getY();
        float pv=y1-y2;
        if(pv<0.0)
            pv=-1.0*pv;
        return pv<distance;
}
// Surcharge de l'opérateur <
   bool PointGL::operator<( PointGL const &rhs)
  {
       bool inf;
       //test if the points have same X
       int roundX=this->x*epsilon ;
        int aX=rhs.getX()*epsilon ;
        bool equals=roundX== aX;
      if(equals){
          //compare z
          inf=(this->getZ() < rhs.getZ());
      }else // compare x
         inf=(this->getX() < rhs.getX());
      return inf;
   }

//   bool PointGL::operator <(const PointGL &rhs1, const PointGL &rhs)
//   {

//       bool inf;
//       //test if the points have same X
//       int roundX=rhs1.getX()*epsilon ;
//        int aX=rhs.getX()*epsilon ;
//        bool equals=roundX== aX;
//      if(equals){
//          //compare z
//          inf=(rhs1.getZ() < rhs.getZ());
//      }else // compare x
//         inf=(rhs1.getX() < rhs.getX());
//      return inf;
//   }
bool PointGL::equals2D(const PointGL a)const{
    //rounded to the thousandth
    int roundX=this->x*epsilon ;
    int roundY=this->y*epsilon ;


    int aX=a.getX()*epsilon ;
    int aY=a.getY()*epsilon ;

    return roundX== aX&&roundY== aY;
}

PointGL::~PointGL() {
}
void PointGL::setNormalMoyenne(std::vector<float> n){
    this->normalMoyenne.clear();
    float z=n[2];
    float y=n[1];
    float x=n[0];
    this->normalMoyenne.push_back(x);
    this->normalMoyenne.push_back(y);
    this->normalMoyenne.push_back(z);
}
void PointGL::setNormalMoyenne(float x, float y, float z){
     this->normalMoyenne.clear();
    this->normalMoyenne.push_back(x);
    this->normalMoyenne.push_back(y);
    this->normalMoyenne.push_back(z);
}
float PointGL::getX() const {
    return this->x;
}
std::vector<float> PointGL::getNormal() const{
    return this->normalMoyenne;
}
float PointGL::getY() const {
    return this->y;
}

float PointGL::getZ() const {
    return this->z;
}

void PointGL::setX(float a) {
    this->x=a;
}

void PointGL::setY(float a) {
    this->y=a;
}

void PointGL::setZ(float a) {
    this->z=a;
}

void PointGL::rotation(float a, int x, int y, int z){
     if(x==1){
        float ay=this->getY();
        float az=this->getZ();
    this->setY(ay*cos(a*rad)-sin(a*rad)*az);
    this->setZ(ay*sin(a*rad)+az*cos(a*rad));
    }
    
    if(y==1){
        float ax=this->getX();
        float az=this->getZ();
    this->setX(ax*cos(a*rad)+az*sin(a*rad));
    this->setZ(-ax*sin(a*rad)+az*cos(a*rad));
    }
    
    if(z==1){
        float ax=this->getX();
        float ay=this->getY();
    this->setX(ax*cos(a*rad)-ay*sin(a*rad));
    this->setY(ax*sin(a*rad)+ay*cos(a*rad));
}
}
void PointGL::translation(float tx, float ty, float tz){
    this->x=this->x+tx;
    this->y=this->y+ty;
    this->z=this->z+tz;
}

void PointGL::scale(float sx, float sy, float sz){
    this->x=this->x*sx;
    this->y=this->y*sy;
    this->z=this->z*sz;
}
