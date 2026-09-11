#include<iostream>
#include"ma_tran_AI.h"
using namespace std;
class bonaoRobot {
    public:
        // Đem cái cỗ máy MAC (chay_tang_noron) của mình VÀO ĐÂY
        void chay_tang_noron(float* input, const float* W, const float* B, float* output, int so_luong_input, int so_luong_output, bool dung_relu) {
            for (int i=0;i<so_luong_output;i++){
         // Bắt đầu bằng Độ lệch (Bias)
         float tong=B[i];
    for(int j=0; j<so_luong_input;j++){
         // Nhân và Cộng dồn (MAC)
        tong += input[j]*W[j*so_luong_output+i];
    }
    // Hàm lọc ReLU (Chỉ chặn số âm nếu bật)
    if(dung_relu && tong<0){
        output [i]=0;

    }
    else{
        output[i]=tong;
    }
    }

        }

        // Tạo 1 cái nút bấm (Hàm) để người dùng ra lệnh dự đoán
        void du_doan_goc(float X, float Y, float Z) {
            float input[3] = {X, Y, Z};
            float out_tang_1[64];
            float out_tang_2[64];
            float out_tang_3[3];

             // 3. LẮP RÁP TẦNG 1 (Từ Input 3 trục -> Phọt ra 64 nơ-ron)
     // true = Bật van ReLU
     chay_tang_noron(input,W_0,B_0,out_tang_1,3,64,true);
     //4. LẮP RÁP TẦNG 2 (Từ 64 nơ-ron Tầng 1 -> Phọt ra 64 nơ-ron Tầng 2)
    // hãy bắt chước dòng trên, tự viết lệnh gọi hàm cho Tầng 2 vào đây:
    // Gợi ý: Dữ liệu vào là out_tang_1. Trọng số là W_1, B_1. Dữ liệu ra là out_tang_2. Bật ReLU (true).
    chay_tang_noron(out_tang_1,W_1,B_1,out_tang_2,64,64,true);
    // 5. LẮP RÁP TẦNG ĐẦU RA (Từ 64 nơ-ron Tầng 2 -> Phọt ra 3 góc Eo, Vai, Khuỷu)
    //  tự viết lệnh gọi hàm cho Tầng 3 vào đây:
    // Gợi ý: Dữ liệu vào là out_tang_2. Dữ liệu ra là out_tang_3.
    // CẢNH BÁO TỬ THẦN: Tầng cuối cùng KHÔNG DÙNG RELU (thay chữ true bằng false)
    chay_tang_noron(out_tang_2,W_2,B_2,out_tang_3,64,3,false);
     // 6. IN KẾT QUẢ ĐỂ NGHIỆM THU

            cout << "Goc Eo: " << out_tang_3[0] << " | Goc Vai: " << out_tang_3[1] << " | Goc Khuyu: " << out_tang_3[2] << endl;
        }
};
int main(){
    bonaoRobot tay_phai;
    bonaoRobot tay_trai;
    cout<<"hai tay dang lam viec cung luc"<<endl;
    //kiem tra hai tay
    cout<<"tay trai dang lay coc nuoc (10,5,10):"<<endl;
    tay_trai.du_doan_goc(10.0,5.0,10.0);
    cout << "TAY PHAI dang nhat mon do khac (8, 2, -5):" << endl;
    tay_phai.du_doan_goc(8.0, 2.0, -5.0);
    return 0;
}