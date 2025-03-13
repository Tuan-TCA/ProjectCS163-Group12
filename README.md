//Cách lấy repo này về máy local để code

Tạo thư mục mới
MỞ thư mục đó trong VScode
Nhập các dòng sau trong terminal
git init #khởi tạo git

git remote add origin https://github.com/Tuan-TCA/ProjectCS163 #liên kết với repos chung của nhóm

git pull origin main #kéo repos về máy local

git checkout -b 'tên branch mới' #tạo branch mới để làm việc (đặt theo tên của mình)

// làm việc trên branch mới này //Sau khi code, thực hiện thay đổi ..v.v.

git add . #thêm các sửa đổi vào vùng stage

git commit -m "tin nhắn commit" #commit các sửa đổi kèm lời nhắn tại local

git push -u origin 'tên branh mới' #đẩy các commit lên remote branch

//Đọc thêm các lệnh về git hoặc học cách sử dụng GitHub Destop