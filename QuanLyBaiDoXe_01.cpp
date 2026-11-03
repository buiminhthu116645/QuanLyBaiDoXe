#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

class Xe {
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int thoiGianDo;
    double phiDoXe;
    bool dangChiemCho;
public:
    Xe();
    Xe(int ma, const string& loai, int gio, int thoiLuong);
    Xe(int ma, const string& loai, int gio, int thoiLuong, double phi, bool trangThai);
    int layMaXe() const;
    string layLoaiXe() const;
    int layGioVao() const;
    int layThoiGianDo() const;
    double layPhiDoXe() const;
    bool layDangChiemCho() const;
    void ganMaXe(int ma);
    void ganLoaiXe(const string& loai);
    void ganGioVao(int gio);
    void ganThoiLuongDo(int thoiLuong);
    void ganPhiDoXe(double phi);
    void ganDangChiemCho(bool trangThai);
    static string chuanHoaLoaiXe(const string& loai);
    static bool laLoaiXeHopLe(const string& loai);
    void tinhPhiDoXe();
    void hienThi() const;
};

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    Xe pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    char lay_kich_thuoc() const;
    void gan_ma(int ma);
    void gan_kich_thuoc(char kt);

    int lay_suc_chua() const;
    int lay_so_xe() const;
    bool da_day() const;

    bool them(const Xe& v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;

    void hien_thi() const;
    void hien_thi_tong_quan() const;
    int hien_thi_theo_loai(const string& loai) const;
    bool co_loai(const string& loai, int& dem, double& tong) const;
};

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3;

    int nhapSoNguyen(const string& thongBao);
    int timViTriBai(int ma);
    bool maXeDaTonTai(int ma);

    void taoBai();
    void themXe();
    void xoaBai();
    void layXeRa();
    void hienThiTatCaBai();
    void hienThiXeTrongBai();
    void lietKeTheoLoai();

    void inTrungBinhHeThong(const string& loai);
    void inTrungBinhTrongBai(const bai_xe& bai, const string& loai);
    void inBaoCaoBai(const bai_xe& bai);
    void xemBaoCao();

public:
    SystemInterface();
    void runMenu();
};

Xe::Xe() {
    maXe = 0;
    loaiXe = "";
    gioVao = 0;
    thoiGianDo = 1;
    phiDoXe = 0;
    dangChiemCho = false;
}

Xe::Xe(int ma, const string& loai, int gio, int thoiLuong) {
    maXe = ma;
    loaiXe = chuanHoaLoaiXe(loai);
    gioVao = gio;
    thoiGianDo = thoiLuong;
    phiDoXe = 0;
    dangChiemCho = false;
    tinhPhiDoXe();
}

Xe::Xe(int ma, const string& loai, int gio, int thoiLuong, double phi, bool trangThai) {
    maXe = ma;
    loaiXe = chuanHoaLoaiXe(loai);
    gioVao = gio;
    thoiGianDo = thoiLuong;
    phiDoXe = phi;
    dangChiemCho = trangThai;
}

int Xe::layMaXe() const { return maXe; }
string Xe::layLoaiXe() const { return loaiXe; }
int Xe::layGioVao() const { return gioVao; }
int Xe::layThoiGianDo() const { return thoiGianDo; }
double Xe::layPhiDoXe() const { return phiDoXe; }
bool Xe::layDangChiemCho() const { return dangChiemCho; }

void Xe::ganMaXe(int ma) { maXe = ma; }

void Xe::ganLoaiXe(const string& loai) {
    string loaiChuan = chuanHoaLoaiXe(loai);
    if (loaiChuan != "") {
        loaiXe = loaiChuan;
    }
}

void Xe::ganGioVao(int gio) {
    if (gio >= 0 && gio <= 23) {
        gioVao = gio;
    }
}

void Xe::ganThoiLuongDo(int thoiLuong) {
    if (thoiLuong >= 1 && thoiLuong <= 23) {
        thoiGianDo = thoiLuong;
    }
}

void Xe::ganPhiDoXe(double phi) { phiDoXe = phi; }
void Xe::ganDangChiemCho(bool trangThai) { dangChiemCho = trangThai; }

string Xe::chuanHoaLoaiXe(const string& loai) {
    string chuThuong = "";
    for (int i = 0; i < (int)loai.length(); i++) {
        chuThuong += (char)tolower(loai[i]);
    }
    if (chuThuong == "car") return "Car";
    if (chuThuong == "motorcycle") return "Motorcycle";
    if (chuThuong == "bicycle") return "Bicycle";
    return "";
}

bool Xe::laLoaiXeHopLe(const string& loai) {
    return chuanHoaLoaiXe(loai) != "";
}

void Xe::tinhPhiDoXe() {
    double donGia = 0;
    if (loaiXe == "Car") donGia = 6.0;
    else if (loaiXe == "Motorcycle") donGia = 4.0;
    else if (loaiXe == "Bicycle") donGia = 2.0;

    bool gioCaoDiem = false;
    if (gioVao >= 6 && gioVao < 10) gioCaoDiem = true;
    if (gioVao >= 15 && gioVao < 19) gioCaoDiem = true;

    double tong = 0;
    for (int gio = 1; gio <= thoiGianDo; gio++) {
        if (gio <= 2) {
            if (gioCaoDiem) tong += donGia * 1.30;
            else tong += donGia * 0.95;
        } else {
            tong += donGia * 0.90;
        }
    }
    phiDoXe = tong;
}

void Xe::hienThi() const {
    cout << "  - Ma xe: " << maXe
         << " | Loai: " << loaiXe
         << " | Gio vao: " << gioVao << "h"
         << " | Thoi gian do: " << thoiGianDo << " gio"
         << " | Phi: " << fixed << setprecision(2) << phiDoXe << endl;
}

bai_xe::bai_xe() {
    ma_bai = 0;
    kich_thuoc = 'S';
    co1 = false;
    co2 = false;
    co3 = false;
}

bai_xe::bai_xe(int ma, char kt) {
    ma_bai = ma;
    kich_thuoc = kt;
    co1 = false;
    co2 = false;
    co3 = false;
}

int bai_xe::lay_ma() const { return ma_bai; }
char bai_xe::lay_kich_thuoc() const { return kich_thuoc; }
void bai_xe::gan_ma(int ma) { ma_bai = ma; }

void bai_xe::gan_kich_thuoc(char kt) {
    if (kt == 'S' || kt == 'M' || kt == 'L') {
        kich_thuoc = kt;
    }
}

int bai_xe::lay_suc_chua() const {
    if (kich_thuoc == 'S') return 1;
    if (kich_thuoc == 'M') return 2;
    return 3;
}

int bai_xe::lay_so_xe() const {
    int dem = 0;
    if (co1) dem++;
    if (co2) dem++;
    if (co3) dem++;
    return dem;
}

bool bai_xe::da_day() const {
    return lay_so_xe() >= lay_suc_chua();
}

bool bai_xe::them(const Xe& v) {
    if (!co1) {
        pt1 = v;
        pt1.ganDangChiemCho(true);
        co1 = true;
        return true;
    }
    if (lay_suc_chua() >= 2 && !co2) {
        pt2 = v;
        pt2.ganDangChiemCho(true);
        co2 = true;
        return true;
    }
    if (lay_suc_chua() >= 3 && !co3) {
        pt3 = v;
        pt3.ganDangChiemCho(true);
        co3 = true;
        return true;
    }
    return false;
}

bool bai_xe::xoa(int ma_xe) {
    if (co1 && pt1.layMaXe() == ma_xe) {
        pt1 = Xe();
        co1 = false;
        return true;
    }
    if (co2 && pt2.layMaXe() == ma_xe) {
        pt2 = Xe();
        co2 = false;
        return true;
    }
    if (co3 && pt3.layMaXe() == ma_xe) {
        pt3 = Xe();
        co3 = false;
        return true;
    }
    return false;
}

bool bai_xe::chua(int ma_xe) const {
    if (co1 && pt1.layMaXe() == ma_xe) return true;
    if (co2 && pt2.layMaXe() == ma_xe) return true;
    if (co3 && pt3.layMaXe() == ma_xe) return true;
    return false;
}

void bai_xe::hien_thi() const {
    cout << "Bai do ID: " << ma_bai << " | Kich thuoc: " << kich_thuoc
         << " | Xe: " << lay_so_xe() << "/" << lay_suc_chua() << endl;
    if (lay_so_xe() == 0) {
        cout << "  (Bai do dang trong)" << endl;
    }
    if (co1) pt1.hienThi();
    if (co2) pt2.hienThi();
    if (co3) pt3.hienThi();
}

void bai_xe::hien_thi_tong_quan() const {
    cout << "Bai ID: " << ma_bai << " | Kich thuoc: " << kich_thuoc
         << " | So xe: " << lay_so_xe() << "/" << lay_suc_chua() << endl;
}

int bai_xe::hien_thi_theo_loai(const string& loai) const {
    int dem = 0;
    if (co1 && pt1.layLoaiXe() == loai) {
        cout << "Bai do " << ma_bai << ":" << endl;
        pt1.hienThi();
        dem++;
    }
    if (co2 && pt2.layLoaiXe() == loai) {
        cout << "Bai do " << ma_bai << ":" << endl;
        pt2.hienThi();
        dem++;
    }
    if (co3 && pt3.layLoaiXe() == loai) {
        cout << "Bai do " << ma_bai << ":" << endl;
        pt3.hienThi();
        dem++;
    }
    return dem;
}

bool bai_xe::co_loai(const string& loai, int& dem, double& tong) const {
    bool thay = false;
    if (co1 && pt1.layLoaiXe() == loai) {
        dem++;
        tong += pt1.layPhiDoXe();
        thay = true;
    }
    if (co2 && pt2.layLoaiXe() == loai) {
        dem++;
        tong += pt2.layPhiDoXe();
        thay = true;
    }
    if (co3 && pt3.layLoaiXe() == loai) {
        dem++;
        tong += pt3.layPhiDoXe();
        thay = true;
    }
    return thay;
}

SystemInterface::SystemInterface() {
    co1 = false;
    co2 = false;
    co3 = false;
}

int SystemInterface::nhapSoNguyen(const string& thongBao) {
    int x;
    cout << thongBao;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nhap sai! Vui long nhap lai: ";
    }
    return x;
}

int SystemInterface::timViTriBai(int ma) {
    if (co1 && bai1.lay_ma() == ma) return 1;
    if (co2 && bai2.lay_ma() == ma) return 2;
    if (co3 && bai3.lay_ma() == ma) return 3;
    return 0;
}

bool SystemInterface::maXeDaTonTai(int ma) {
    if (co1 && bai1.chua(ma)) return true;
    if (co2 && bai2.chua(ma)) return true;
    if (co3 && bai3.chua(ma)) return true;
    return false;
}

void SystemInterface::taoBai() {
    if (co1 && co2 && co3) {
        cout << "Da du 3 bai do, khong the tao them!" << endl;
        return;
    }
    int ma = nhapSoNguyen("Nhap ma bai: ");
    if (ma <= 0) {
        cout << "Ma bai phai la so duong!" << endl;
        return;
    }
    if (timViTriBai(ma) != 0) {
        cout << "Ma bai da ton tai!" << endl;
        return;
    }
    char kichThuoc;
    cout << "Nhap kich thuoc (S/M/L): ";
    cin >> kichThuoc;
    kichThuoc = (char)toupper(kichThuoc);
    if (kichThuoc != 'S' && kichThuoc != 'M' && kichThuoc != 'L') {
        cout << "Kich thuoc khong hop le!" << endl;
        return;
    }

    if (!co1) {
        bai1 = bai_xe(ma, kichThuoc);
        co1 = true;
    } else if (!co2) {
        bai2 = bai_xe(ma, kichThuoc);
        co2 = true;
    } else {
        bai3 = bai_xe(ma, kichThuoc);
        co3 = true;
    }
    cout << "Tao bai do thanh cong!" << endl;
}

void SystemInterface::themXe() {
    if (!co1 && !co2 && !co3) {
        cout << "Chua co bai do nao, hay tao bai do truoc!" << endl;
        return;
    }

    int ma = nhapSoNguyen("Nhap ma xe: ");
    if (ma <= 0) {
        cout << "Ma xe phai la so duong!" << endl;
        return;
    }
    if (maXeDaTonTai(ma)) {
        cout << "Ma xe da ton tai!" << endl;
        return;
    }

    string loai;
    cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
    cin >> loai;
    if (!Xe::laLoaiXeHopLe(loai)) {
        cout << "Loai xe khong hop le!" << endl;
        return;
    }
    string loaiChuan = Xe::chuanHoaLoaiXe(loai);

    int gioVao = nhapSoNguyen("Nhap gio vao (0-23): ");
    if (gioVao < 0 || gioVao > 23) {
        cout << "Gio vao khong hop le!" << endl;
        return;
    }
    int thoiGian = nhapSoNguyen("Nhap so gio do (1-23): ");
    if (thoiGian < 1 || thoiGian > 23) {
        cout << "So gio do khong hop le!" << endl;
        return;
    }
    if (gioVao + thoiGian > 24) {
        cout << "Xe phai ra khoi bai trong cung ngay!" << endl;
        return;
    }

    Xe xe(ma, loaiChuan, gioVao, thoiGian);

    if (co1 && !bai1.da_day()) {
        bai1.them(xe);
        cout << "Da xep xe vao bai " << bai1.lay_ma() << endl;
    } else if (co2 && !bai2.da_day()) {
        bai2.them(xe);
        cout << "Da xep xe vao bai " << bai2.lay_ma() << endl;
    } else if (co3 && !bai3.da_day()) {
        bai3.them(xe);
        cout << "Da xep xe vao bai " << bai3.lay_ma() << endl;
    } else {
        cout << "Tat ca bai do da day!" << endl;
        return;
    }
    cout << "Phi do xe: " << fixed << setprecision(2) << xe.layPhiDoXe() << endl;
}

void SystemInterface::xoaBai() {
    int ma = nhapSoNguyen("Nhap ma bai can xoa: ");
    int viTri = timViTriBai(ma);
    if (viTri == 0) {
        cout << "Khong tim thay bai do!" << endl;
        return;
    }
    if (viTri == 1) {
        bai1 = bai_xe();
        co1 = false;
    } else if (viTri == 2) {
        bai2 = bai_xe();
        co2 = false;
    } else {
        bai3 = bai_xe();
        co3 = false;
    }
    cout << "Da xoa bai do (cac xe trong bai cung bi xoa)." << endl;
}

void SystemInterface::layXeRa() {
    int ma = nhapSoNguyen("Nhap ma xe can lay ra: ");
    bool thanhCong = false;
    if (co1 && bai1.xoa(ma)) thanhCong = true;
    else if (co2 && bai2.xoa(ma)) thanhCong = true;
    else if (co3 && bai3.xoa(ma)) thanhCong = true;

    if (thanhCong) cout << "Da lay xe ra khoi bai!" << endl;
    else cout << "Khong tim thay xe!" << endl;
}

void SystemInterface::hienThiTatCaBai() {
    if (!co1 && !co2 && !co3) {
        cout << "Chua co bai do nao!" << endl;
        return;
    }
    if (co1) bai1.hien_thi_tong_quan();
    if (co2) bai2.hien_thi_tong_quan();
    if (co3) bai3.hien_thi_tong_quan();
}

void SystemInterface::hienThiXeTrongBai() {
    int ma = nhapSoNguyen("Nhap ma bai: ");
    int viTri = timViTriBai(ma);
    if (viTri == 1) bai1.hien_thi();
    else if (viTri == 2) bai2.hien_thi();
    else if (viTri == 3) bai3.hien_thi();
    else cout << "Khong tim thay bai do!" << endl;
}

void SystemInterface::lietKeTheoLoai() {
    string loai;
    cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
    cin >> loai;
    if (!Xe::laLoaiXeHopLe(loai)) {
        cout << "Loai xe khong hop le!" << endl;
        return;
    }
    string loaiChuan = Xe::chuanHoaLoaiXe(loai);

    int dem = 0;
    if (co1) dem += bai1.hien_thi_theo_loai(loaiChuan);
    if (co2) dem += bai2.hien_thi_theo_loai(loaiChuan);
    if (co3) dem += bai3.hien_thi_theo_loai(loaiChuan);

    if (dem == 0) cout << "Khong co xe loai " << loaiChuan << " nao." << endl;
}

void SystemInterface::inTrungBinhHeThong(const string& loai) {
    int dem = 0;
    double tong = 0;
    if (co1) bai1.co_loai(loai, dem, tong);
    if (co2) bai2.co_loai(loai, dem, tong);
    if (co3) bai3.co_loai(loai, dem, tong);

    cout << loai << ": ";
    if (dem == 0) cout << "khong co xe" << endl;
    else cout << fixed << setprecision(2) << tong / dem << " (" << dem << " xe)" << endl;
}

void SystemInterface::inTrungBinhTrongBai(const bai_xe& bai, const string& loai) {
    int dem = 0;
    double tong = 0;
    cout << "  " << loai << ": ";
    if (bai.co_loai(loai, dem, tong)) {
        cout << fixed << setprecision(2) << tong / dem << " (" << dem << " xe)" << endl;
    } else {
        cout << "khong co xe" << endl;
    }
}

void SystemInterface::inBaoCaoBai(const bai_xe& bai) {
    cout << "Bai do " << bai.lay_ma() << ":" << endl;
    inTrungBinhTrongBai(bai, "Car");
    inTrungBinhTrongBai(bai, "Motorcycle");
    inTrungBinhTrongBai(bai, "Bicycle");
}

void SystemInterface::xemBaoCao() {
    if (!co1 && !co2 && !co3) {
        cout << "Chua co bai do nao!" << endl;
        return;
    }
    cout << "--- Phi trung binh toan he thong ---" << endl;
    inTrungBinhHeThong("Car");
    inTrungBinhHeThong("Motorcycle");
    inTrungBinhHeThong("Bicycle");

    cout << "--- Chi tiet theo tung bai ---" << endl;
    if (co1) inBaoCaoBai(bai1);
    if (co2) inBaoCaoBai(bai2);
    if (co3) inBaoCaoBai(bai3);
}

void SystemInterface::runMenu() {
    int luaChon;
    do {
        cout << "\n===== QUAN LY BAI DO XE =====" << endl;
        cout << "1. Tao bai do xe moi" << endl;
        cout << "2. Them xe vao bai do" << endl;
        cout << "3. Xoa mot bai do xe" << endl;
        cout << "4. Lay xe ra khoi bai do" << endl;
        cout << "5. Hien thi danh sach tat ca cac bai do" << endl;
        cout << "6. Hien thi danh sach xe theo bai cu the" << endl;
        cout << "7. Liet ke xe theo loai phuong tien" << endl;
        cout << "8. Xem bao cao phi do xe trung binh" << endl;
        cout << "9. Thoat chuong trinh" << endl;
        luaChon = nhapSoNguyen("Chon chuc nang: ");

        switch (luaChon) {
            case 1: taoBai(); break;
            case 2: themXe(); break;
            case 3: xoaBai(); break;
            case 4: layXeRa(); break;
            case 5: hienThiTatCaBai(); break;
            case 6: hienThiXeTrongBai(); break;
            case 7: lietKeTheoLoai(); break;
            case 8: xemBaoCao(); break;
            case 9: cout << "Tam biet!" << endl; break;
            default: cout << "Lua chon khong hop le!" << endl;
        }
    } while (luaChon != 9);
}

int main() {
    SystemInterface heThong;
    heThong.runMenu();
    return 0;
}