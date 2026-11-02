#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

class Vehicle {
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int thoiGianDo;
    double phiDoXe;
    bool dangCoXe;

public:
    Vehicle() {
        maXe = 0;
        loaiXe = "";
        gioVao = 0;
        thoiGianDo = 1;
        phiDoXe = 0;
        dangCoXe = false;
    }

    Vehicle(int ma, string loai, int gio, int thoiGian, double phi, bool coXe) {
        maXe = ma;
        loaiXe = chuanHoaLoaiXe(loai);
        gioVao = gio;
        thoiGianDo = thoiGian;
        phiDoXe = phi;
        dangCoXe = coXe;
    }

    string chuanHoaLoaiXe(string loai) const {
        string chuThuong = "";
        for (int i = 0; i < (int)loai.length(); i++) {
            chuThuong += (char)tolower(loai[i]);
        }
        if (chuThuong == "car") return "Car";
        if (chuThuong == "motorcycle") return "Motorcycle";
        if (chuThuong == "bicycle") return "Bicycle";
        return "";
    }

    int getMaXe() const { return maXe; }
    string getLoaiXe() const { return loaiXe; }
    int getGioVao() const { return gioVao; }
    int getThoiGianDo() const { return thoiGianDo; }
    double getPhiDoXe() const { return phiDoXe; }
    bool getDangCoXe() const { return dangCoXe; }

    void setMaXe(int ma) { maXe = ma; }
    void setLoaiXe(string loai) {
        string loaiChuan = chuanHoaLoaiXe(loai);
        if (loaiChuan != "") {
            loaiXe = loaiChuan;
        }
    }
    void setGioVao(int gio) {
        if (gio >= 0 && gio <= 23) gioVao = gio;
    }
    void setThoiGianDo(int thoiGian) {
        if (thoiGian >= 1 && thoiGian <= 23) thoiGianDo = thoiGian;
    }
    void setPhiDoXe(double phi) { phiDoXe = phi; }
    void setDangCoXe(bool coXe) { dangCoXe = coXe; }

    void calculateFee() {
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
                if (gioCaoDiem) tong += donGia * 1.3;
                else tong += donGia * 0.95;
            } else {
                tong += donGia * 0.9;
            }
        }
        phiDoXe = tong;
    }

    void display() const {
        cout << "  - Ma xe: " << maXe
             << " | Loai: " << loaiXe
             << " | Gio vao: " << gioVao << "h"
             << " | Thoi gian do: " << thoiGianDo << " gio"
             << " | Phi: " << fixed << setprecision(2) << phiDoXe << endl;
    }
};

class ParkingLot {
private:
    int maBai;
    char kichThuoc;
    Vehicle xe1;
    Vehicle xe2;
    Vehicle xe3;
    bool coXe1;
    bool coXe2;
    bool coXe3;

public:
    ParkingLot() {
        maBai = 0;
        kichThuoc = 'S';
        coXe1 = false;
        coXe2 = false;
        coXe3 = false;
    }

    ParkingLot(int ma, char kt) {
        maBai = ma;
        kichThuoc = kt;
        coXe1 = false;
        coXe2 = false;
        coXe3 = false;
    }

    int getMaBai() const { return maBai; }
    char getKichThuoc() const { return kichThuoc; }
    void setMaBai(int ma) { maBai = ma; }
    void setKichThuoc(char kt) { kichThuoc = kt; }

    int getSucChua() const {
        if (kichThuoc == 'S') return 1;
        if (kichThuoc == 'M') return 2;
        return 3;
    }

    int getSoXe() const {
        int dem = 0;
        if (coXe1) dem++;
        if (coXe2) dem++;
        if (coXe3) dem++;
        return dem;
    }

    bool daDay() const {
        return getSoXe() >= getSucChua();
    }

    bool coMaXe(int ma) const {
        if (coXe1 && xe1.getMaXe() == ma) return true;
        if (coXe2 && xe2.getMaXe() == ma) return true;
        if (coXe3 && xe3.getMaXe() == ma) return true;
        return false;
    }

    bool addVehicle(const Vehicle& v) {
        if (!coXe1) {
            xe1 = v;
            xe1.setDangCoXe(true);
            coXe1 = true;
            return true;
        }
        if (getSucChua() >= 2 && !coXe2) {
            xe2 = v;
            xe2.setDangCoXe(true);
            coXe2 = true;
            return true;
        }
        if (getSucChua() >= 3 && !coXe3) {
            xe3 = v;
            xe3.setDangCoXe(true);
            coXe3 = true;
            return true;
        }
        return false;
    }

    bool removeVehicle(int vID) {
        if (coXe1 && xe1.getMaXe() == vID) {
            xe1 = Vehicle();
            coXe1 = false;
            return true;
        }
        if (coXe2 && xe2.getMaXe() == vID) {
            xe2 = Vehicle();
            coXe2 = false;
            return true;
        }
        if (coXe3 && xe3.getMaXe() == vID) {
            xe3 = Vehicle();
            coXe3 = false;
            return true;
        }
        return false;
    }

    int demTheoLoai(string loai) const {
        int dem = 0;
        if (coXe1 && xe1.getLoaiXe() == loai) dem++;
        if (coXe2 && xe2.getLoaiXe() == loai) dem++;
        if (coXe3 && xe3.getLoaiXe() == loai) dem++;
        return dem;
    }

    double tongPhiTheoLoai(string loai) const {
        double tong = 0;
        if (coXe1 && xe1.getLoaiXe() == loai) tong += xe1.getPhiDoXe();
        if (coXe2 && xe2.getLoaiXe() == loai) tong += xe2.getPhiDoXe();
        if (coXe3 && xe3.getLoaiXe() == loai) tong += xe3.getPhiDoXe();
        return tong;
    }

    int inTheoLoai(string loai) const {
        int dem = 0;
        if (coXe1 && xe1.getLoaiXe() == loai) {
            cout << "Bai do " << maBai << ":" << endl;
            xe1.display();
            dem++;
        }
        if (coXe2 && xe2.getLoaiXe() == loai) {
            cout << "Bai do " << maBai << ":" << endl;
            xe2.display();
            dem++;
        }
        if (coXe3 && xe3.getLoaiXe() == loai) {
            cout << "Bai do " << maBai << ":" << endl;
            xe3.display();
            dem++;
        }
        return dem;
    }

    void displayLotInfo() const {
        cout << "Bai do ID: " << maBai << " | Kich thuoc: " << kichThuoc
             << " | Xe: " << getSoXe() << "/" << getSucChua() << endl;
        if (getSoXe() == 0) {
            cout << "  (Bai do dang trong)" << endl;
        }
        if (coXe1) xe1.display();
        if (coXe2) xe2.display();
        if (coXe3) xe3.display();
    }
};

class SystemInterface {
private:
    ParkingLot baiDo1;
    ParkingLot baiDo2;
    ParkingLot baiDo3;
    bool coBai1;
    bool coBai2;
    bool coBai3;

    int nhapSoNguyen(string thongBao) {
        int x;
        cout << thongBao;
        while (!(cin >> x)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Nhap sai! Vui long nhap lai: ";
        }
        return x;
    }

    int timViTriBai(int ma) {
        if (coBai1 && baiDo1.getMaBai() == ma) return 1;
        if (coBai2 && baiDo2.getMaBai() == ma) return 2;
        if (coBai3 && baiDo3.getMaBai() == ma) return 3;
        return 0;
    }

    bool maXeDaTonTai(int ma) {
        if (coBai1 && baiDo1.coMaXe(ma)) return true;
        if (coBai2 && baiDo2.coMaXe(ma)) return true;
        if (coBai3 && baiDo3.coMaXe(ma)) return true;
        return false;
    }

    void taoBaiDo() {
        if (coBai1 && coBai2 && coBai3) {
            cout << "Da du 3 bai do, khong the tao them!" << endl;
            return;
        }
        int ma = nhapSoNguyen("Nhap parkID: ");
        if (ma <= 0) {
            cout << "parkID phai la so duong!" << endl;
            return;
        }
        if (timViTriBai(ma) != 0) {
            cout << "parkID da ton tai!" << endl;
            return;
        }
        char kichThuoc;
        cout << "Nhap kich thuoc (S/M/L): ";
        cin >> kichThuoc;
        kichThuoc = toupper(kichThuoc);
        if (kichThuoc != 'S' && kichThuoc != 'M' && kichThuoc != 'L') {
            cout << "Kich thuoc khong hop le!" << endl;
            return;
        }

        if (!coBai1) {
            baiDo1 = ParkingLot(ma, kichThuoc);
            coBai1 = true;
        } else if (!coBai2) {
            baiDo2 = ParkingLot(ma, kichThuoc);
            coBai2 = true;
        } else {
            baiDo3 = ParkingLot(ma, kichThuoc);
            coBai3 = true;
        }
        cout << "Tao bai do thanh cong!" << endl;
    }

    void themXe() {
        if (!coBai1 && !coBai2 && !coBai3) {
            cout << "Chua co bai do nao, hay tao bai do truoc!" << endl;
            return;
        }

        Vehicle xe;
        int ma = nhapSoNguyen("Nhap vehicleID: ");
        if (ma <= 0) {
            cout << "vehicleID phai la so duong!" << endl;
            return;
        }
        if (maXeDaTonTai(ma)) {
            cout << "vehicleID da ton tai!" << endl;
            return;
        }

        string loai;
        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
        cin >> loai;
        string loaiChuan = xe.chuanHoaLoaiXe(loai);
        if (loaiChuan == "") {
            cout << "Loai xe khong hop le!" << endl;
            return;
        }

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

        xe.setMaXe(ma);
        xe.setLoaiXe(loaiChuan);
        xe.setGioVao(gioVao);
        xe.setThoiGianDo(thoiGian);
        xe.calculateFee();

        if (coBai1 && !baiDo1.daDay()) {
            baiDo1.addVehicle(xe);
            cout << "Da xep xe vao bai " << baiDo1.getMaBai() << endl;
        } else if (coBai2 && !baiDo2.daDay()) {
            baiDo2.addVehicle(xe);
            cout << "Da xep xe vao bai " << baiDo2.getMaBai() << endl;
        } else if (coBai3 && !baiDo3.daDay()) {
            baiDo3.addVehicle(xe);
            cout << "Da xep xe vao bai " << baiDo3.getMaBai() << endl;
        } else {
            cout << "Tat ca bai do da day!" << endl;
            return;
        }
        cout << "Phi do xe: " << fixed << setprecision(2) << xe.getPhiDoXe() << endl;
    }

    void xoaBaiDo() {
        int ma = nhapSoNguyen("Nhap parkID can xoa: ");
        int viTri = timViTriBai(ma);
        if (viTri == 0) {
            cout << "Khong tim thay bai do!" << endl;
            return;
        }
        if (viTri == 1) {
            baiDo1 = ParkingLot();
            coBai1 = false;
        } else if (viTri == 2) {
            baiDo2 = ParkingLot();
            coBai2 = false;
        } else {
            baiDo3 = ParkingLot();
            coBai3 = false;
        }
        cout << "Da xoa bai do (cac xe trong bai cung bi xoa)." << endl;
    }

    void layXeRa() {
        int ma = nhapSoNguyen("Nhap vehicleID can lay ra: ");
        bool thanhCong = false;
        if (coBai1 && baiDo1.removeVehicle(ma)) thanhCong = true;
        else if (coBai2 && baiDo2.removeVehicle(ma)) thanhCong = true;
        else if (coBai3 && baiDo3.removeVehicle(ma)) thanhCong = true;

        if (thanhCong) cout << "Da lay xe ra khoi bai!" << endl;
        else cout << "Khong tim thay xe!" << endl;
    }

    void hienThiTatCaBai() {
        if (!coBai1 && !coBai2 && !coBai3) {
            cout << "Chua co bai do nao!" << endl;
            return;
        }
        if (coBai1) {
            cout << "Bai ID: " << baiDo1.getMaBai() << " | Size: " << baiDo1.getKichThuoc()
                 << " | So xe: " << baiDo1.getSoXe() << "/" << baiDo1.getSucChua() << endl;
        }
        if (coBai2) {
            cout << "Bai ID: " << baiDo2.getMaBai() << " | Size: " << baiDo2.getKichThuoc()
                 << " | So xe: " << baiDo2.getSoXe() << "/" << baiDo2.getSucChua() << endl;
        }
        if (coBai3) {
            cout << "Bai ID: " << baiDo3.getMaBai() << " | Size: " << baiDo3.getKichThuoc()
                 << " | So xe: " << baiDo3.getSoXe() << "/" << baiDo3.getSucChua() << endl;
        }
    }

    void hienThiXeTrongBai() {
        int ma = nhapSoNguyen("Nhap parkID: ");
        int viTri = timViTriBai(ma);
        if (viTri == 1) baiDo1.displayLotInfo();
        else if (viTri == 2) baiDo2.displayLotInfo();
        else if (viTri == 3) baiDo3.displayLotInfo();
        else cout << "Khong tim thay bai do!" << endl;
    }

    void lietKeTheoLoai() {
        Vehicle xeTam;
        string loai;
        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
        cin >> loai;
        string loaiChuan = xeTam.chuanHoaLoaiXe(loai);
        if (loaiChuan == "") {
            cout << "Loai xe khong hop le!" << endl;
            return;
        }

        int dem = 0;
        if (coBai1) dem += baiDo1.inTheoLoai(loaiChuan);
        if (coBai2) dem += baiDo2.inTheoLoai(loaiChuan);
        if (coBai3) dem += baiDo3.inTheoLoai(loaiChuan);

        if (dem == 0) cout << "Khong co xe loai " << loaiChuan << " nao." << endl;
    }

    void inTrungBinhHeThong(string loai) {
        int dem = 0;
        double tong = 0;
        if (coBai1) {
            dem += baiDo1.demTheoLoai(loai);
            tong += baiDo1.tongPhiTheoLoai(loai);
        }
        if (coBai2) {
            dem += baiDo2.demTheoLoai(loai);
            tong += baiDo2.tongPhiTheoLoai(loai);
        }
        if (coBai3) {
            dem += baiDo3.demTheoLoai(loai);
            tong += baiDo3.tongPhiTheoLoai(loai);
        }
        cout << loai << ": ";
        if (dem == 0) cout << "khong co xe" << endl;
        else cout << fixed << setprecision(2) << tong / dem << " (" << dem << " xe)" << endl;
    }

    void inTrungBinhTrongBai(const ParkingLot& bai, string loai) {
        int dem = bai.demTheoLoai(loai);
        cout << "  " << loai << ": ";
        if (dem == 0) cout << "khong co xe" << endl;
        else cout << fixed << setprecision(2) << bai.tongPhiTheoLoai(loai) / dem
                  << " (" << dem << " xe)" << endl;
    }

    void inBaoCaoBai(const ParkingLot& bai) {
        cout << "Bai do " << bai.getMaBai() << ":" << endl;
        inTrungBinhTrongBai(bai, "Car");
        inTrungBinhTrongBai(bai, "Motorcycle");
        inTrungBinhTrongBai(bai, "Bicycle");
    }

    void xemBaoCao() {
        if (!coBai1 && !coBai2 && !coBai3) {
            cout << "Chua co bai do nao!" << endl;
            return;
        }
        cout << "--- Phi trung binh toan he thong ---" << endl;
        inTrungBinhHeThong("Car");
        inTrungBinhHeThong("Motorcycle");
        inTrungBinhHeThong("Bicycle");

        cout << "--- Chi tiet theo tung bai ---" << endl;
        if (coBai1) inBaoCaoBai(baiDo1);
        if (coBai2) inBaoCaoBai(baiDo2);
        if (coBai3) inBaoCaoBai(baiDo3);
    }

public:
    SystemInterface() {
        coBai1 = false;
        coBai2 = false;
        coBai3 = false;
    }

    void runMenu() {
        int luaChon;
        do {
            cout << "\n===== QUAN LY BAI DO XE =====" << endl;
            cout << "1. Tao bai do xe moi" << endl;
            cout << "2. Them xe vao bai do" << endl;
            cout << "3. Xoa mot bai do xe" << endl;
            cout << "4. Lay xe ra khoi bai do" << endl;
            cout << "5. Hien thi danh sach cac bai do" << endl;
            cout << "6. Hien thi danh sach xe theo bai" << endl;
            cout << "7. Liet ke xe theo loai" << endl;
            cout << "8. Bao cao phi do xe trung binh" << endl;
            cout << "9. Thoat" << endl;
            luaChon = nhapSoNguyen("Chon chuc nang: ");

            switch (luaChon) {
                case 1: taoBaiDo(); break;
                case 2: themXe(); break;
                case 3: xoaBaiDo(); break;
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
};

int main() {
    SystemInterface heThong;
    heThong.runMenu();
    return 0;
}