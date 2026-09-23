#include<iostream>
#include<cmath>
#include<string>
#include<vector>
using namespace std;
//tạo khớp cho robot human
class joint{
    public:
    string name;
    //tính góc bằng độ degree
    double angle;
    //góc gập đối đa
    double max_limit;
    //góc duỗi tối đa
    double min_limit;
    double goc_hien_tai;
    //khai sinh ra khớp
      joint(string _name, double _min, double _max){
         name=_name;
        min_limit=_min;
        max_limit=_max;
        goc_hien_tai=0.0;
     }

};
//cánh tay robothuman
class canhtayrobot{
    public:
    vector<joint>cac_khop_canh_tay;
    double L1=15.0;
    double L2=13.0;
    double L3=5.0;
    void lap_rap_cac_khop(){
      cac_khop_canh_tay.push_back(joint("khop_de",-180,180));
      cac_khop_canh_tay.push_back(joint("khop vai",-90,90));
      cac_khop_canh_tay.push_back(joint("khop khuyu",0,150));
      cac_khop_canh_tay.push_back(joint("khop co tay 1",-90,90));
      cac_khop_canh_tay.push_back(joint("khop co tay 2",-180,180));
}

//thuật toán IK
      void chay_thuat_toan_Ik(double X_muc_tieu, double Y_muc_tieu, double Z_muc_tieu) {
        cout << "\n>>> Dang tinh toan IK 5-DOF di toi toa do: (" 
             << X_muc_tieu << ", " << Y_muc_tieu << ", " << Z_muc_tieu << ")" << endl;  
      //thuật toán IK
      double D_3d=sqrt((X_muc_tieu*X_muc_tieu)+(Y_muc_tieu*Y_muc_tieu)+(Z_muc_tieu*Z_muc_tieu));
      int chieu_dai_canh_tay=L1+L2+L3;
      if (D_3d>chieu_dai_canh_tay)
      {
            cout<<"muc tieu xa tam voi, khong the voi toi"<<D_3d<<endl;
      }
      else if (X_muc_tieu<=0)
      {
            cout<<"toa do X nam sat buc tuong"<<endl;
      }
      else if (Y_muc_tieu<=0)
      {
            cout<<"toa do Y nam sat buc tuong"<<endl; 
      }
      else{
            cout<<"thong so hop le robot dang tinh toa do"<<endl;
      }
      //tính IK
      //dùng atan2
      double goc_eo_rad=atan2(Z_muc_tieu,X_muc_tieu);
      double goc_eo_do=goc_eo_rad*180/3.141592;
      cout<<"goc eo can quay la: "<<goc_eo_do<<"do"<<endl;
      //3d to 2d
      //pytago
      double X_moi=sqrt((X_muc_tieu*X_muc_tieu)+(Z_muc_tieu*Z_muc_tieu));
      // tong binh phuong sqrt
      double tong_binh_phuong=(X_moi*X_moi)+(Y_muc_tieu*Y_muc_tieu);
      double D_2d=sqrt(tong_binh_phuong);
      int canh_tay_co_chieu_dai=L1+L2+L3;
      if(D_2d > canh_tay_co_chieu_dai) {
            cout<<"[LOI] Muc tieu qua xa robot, khoang cach la: "<<D_2d<<endl;
            cout<<"[CANH BAO] Ngung tinh toan de bao ve motor!"<<endl;
            return; // <--- PHẢI CÓ DÒNG NÀY ĐỂ THOÁT HÀM, KHÔNG CHẠY TIẾP
      }      
      else {
            cout<<"[OK] Muc tieu trong tam tay. Chuan bi tinh toan 5-DOF"<<endl;
            
            // BÍ KÍP TÁCH CỔ TAY (Wrist Decoupling)
            // Lùi lại một khoảng L3 để tìm vị trí Cổ tay
            double D_cotay = D_2d - L3; 

            // Bây giờ áp dụng Cosin cho Tam giác (L1, L2, D_cotay)
            double tu_so = (D_cotay*D_cotay) - (L1*L1) - (L2*L2);
            double mau_so = 2 * L1 * L2; // <-- Thấy chưa, chỉ có L1 và L2 thôi!
            double goc_khuyu = tu_so / mau_so;
            
            // Dịch ngược radian bằng hàm acos
            double goc_khuyu_rad = acos(goc_khuyu);
            double goc_khuyu_do = goc_khuyu_rad * 180 / 3.141592;
            cout << " Goc Khuyu (Elbow) can quay: " << goc_khuyu_do << " do" << endl;
            
            // Tính góc Vai
            double goc_huong = atan2(Y_muc_tieu, X_moi);
            double goc_bu_tru = atan2(L2 * sin(goc_khuyu_rad), L1 + L2 * cos(goc_khuyu_rad));
            
            double goc_vai_rad = goc_huong - goc_bu_tru;
            double goc_vai_do = goc_vai_rad * 180 / 3.141592;
            cout << " Goc Vai (Shoulder) can quay: " << goc_vai_do << " do" << endl;
            // 1. Góc bàn tay mong muốn: Bạn muốn bưng ly nước không bị đổ 
            // -> Bàn tay phải song song với mặt đất (Giả sử là 0 độ)
            double goc_ban_tay_mong_muon = 0.0; 

            // 2. Cổ tay 1 (Pitch) tự động gập lại để "bù trừ" cho Vai và Khuỷu
            double goc_co_tay_1_do = goc_ban_tay_mong_muon - (goc_vai_do + goc_khuyu_do);
            cout << " Goc Co Tay 1 (Pitch) can quay: " << goc_co_tay_1_do << " do" << endl;

            // 3. Cổ tay 2 (Roll - Vặn tay nắm cửa)
            // Vì bưng ly nước không cần vặn xoắn cổ tay, nên ta vẫn giữ nó là 0.
            double goc_co_tay_2_do = 0.0;
            cout << " Goc Co Tay 2 (Roll) can quay: " << goc_co_tay_2_do << " do" << endl;
      }


      }
};
int main(){
      canhtayrobot tay_phai;
      tay_phai.lap_rap_cac_khop();
      //lấy quyển sách tọa độ X=10, Y=10, Z=5
      tay_phai.chay_thuat_toan_Ik(10.0,10.0,5);
      return 0;
}

