#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;
//main
int main(){
    int L1=12;
    int L2=15;
    double X=15;
    double Y=12;
    double Z=10;
    //CSV
    ofstream file_data("dataset_robot3d_CSV");
    double D_3d=sqrt((X*X)+(Y*Y)+(Z*Z));
    int chieu_dai_canh_tay=L1+L2;
    if (D_3d>chieu_dai_canh_tay)
    {
        cout<<"muc tieu xa tam tay,khong the voi toi"<<D_3d<<endl;
    }
    else if (X<=0)
    {
        cout<<"toa do X nam sat buc tuong"<<endl;
    }
    else if (Y<=0)
    {
        cout<<"toa do Y nam sat buc tuong"<<endl;
    }
    else{
        cout<<"he thong hop le dang tinh IK"<<endl;
        //tính IK
        //tính eo dùng atan2
        double goc_eo_rad=atan2(Z,X);
        double goc_eo_do=goc_eo_rad*180/3.141592;
        cout<<"goc eo can quay la:"<<goc_eo_do<<"do"<<endl;
        //từ 3d sang 2d
        //pytago
        double X_moi=sqrt((X*X)+(Z*Z));
        //tính tổng bình phương
        double tong_binh_phuong=(X_moi*X_moi)+(Y*Y);
        double D_2d= sqrt(tong_binh_phuong);
        int canh_tay_vuon_dai=L1+L2;
        if (D_2d>canh_tay_vuon_dai)
        {
            cout<<" muc tieu qua xa, khoang cach la:"<<D_2d<<endl;
            cout<<"canh bao muc tieu qua xa "<<endl;
        }
        else
        {
            cout<<"muc tieu trong tam tay, khoang cach la:"<<D_2d<<endl;
            cout<<"chuan bi tinh cac khop"<<endl;
            //tính cosin
            double tu_so=tong_binh_phuong-(L1*L1)-(L2*L2);
            double mau_so=2*L1*L2;
            double goc_khuyu=tu_so/mau_so;
            //diịch ngược radian bằng hàm acos
            double goc_khuyu_rad=acos(goc_khuyu);
            //đổi sang độ bằng toán học
            double goc_khuyu_do=goc_khuyu_rad*180/3.141592;
            //in ra màn hình
            cout<<"goc khuyu tay can quay la:"<<goc_khuyu_do<<"do"<<endl;
            //tính góc hướng
            double goc_huong=atan2(Y,X_moi);
            //tính góc bù trừ
            double goc_bu_tru=atan2(L2*sin(goc_khuyu_rad),L1+L2*cos(goc_khuyu_rad));
            //tinh gốc vai
             double goc_vai_rad=goc_huong-goc_bu_tru;
            //tính gốc vai độ
            double goc_vai_do=goc_vai_rad*180/3.141592;
            //in ra màn hình
            file_data << X << "," << Y << "," << Z << "," 
              << goc_eo_do << "," << goc_vai_do << "," << goc_khuyu_do << endl;
        }
    } 
    file_data.close();
     cout << "Da luu du lieu thanh cong vao file CSV!" << endl;
    return 0;
}

