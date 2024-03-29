# SDL2-Tetris-Game-INT2215-UET
### Video Demo https://youtu.be/9wpVOchaK8I
## Table Of Contents <br />
* [Hướng dẫn cài đặt](#setup)
* [Mô tả chung](#info)
* [Các chức năng](#detail)
* [Kỹ thuật lập trình](#tech)
* [Các hướng đi trong tương lai](#future)
* [Kết luận](#summary)


* <a name="setup"/>
## 1. Hướng dẫn cài đặt
- Để khởi động trò chơi, click main.exe. <br />


* <a name="info"/>
## 2. Mô tả chung <br />

### Giới thiệu
Tetris hay Xếp Hình (1984), trò chơi có 7 loại Khối Hình (Tetromino) I (thẳng đứng), J, L, O (vuông), S, T, Z ứng với 7 màu khác nhau. <br />

### Về Game Mechanics <br />
- Cấu tạo: Mỗi Khối Hình được cấu tạo từ 4 khối gạch vuông (Block). Các Khối Hình có thể xoay được các góc 90, 180, 270 độ. <br />
- Mục tiêu: Di chuyển các khối gạch đang rơi từ từ xuống trong kích thước hình chữ nhật 20 hàng x 10 cột (trên màn hình).  <br />
- Chỗ nào có gạch rồi thì không di chuyển được tới vị trí đó. <br />
- Người chơi xếp những khối hình sao cho khối hình lấp đầy 1 hàng ngang để ghi điểm và hàng ngang ấy sẽ biến mất và người chơi sẽ ghi điểm. <br />
- Người chơi thua cuộc khi Khối Hình tràn ra trên 2 dòng khỏi Grid (Lưới). <br />

* <a name="detail"/>
## 3. Các chức năng
Để thoát game, nhấn ESC.<br />
### 1. Chức năng Play Single <br />
Chức năng cơ bản nhất của game. Chơi như trên mô tả, cách chơi cụ thể ở hình minh họa dưới mục "Chức năng Help" ^^. <br />
![image](https://user-images.githubusercontent.com/94885088/170222565-b1ef89e6-0eab-4fd7-89fa-539e6a7b6725.png)
- Hold <C> : Ấn để giữ lại khối hình hiện tại, khối hình hiện tại được thay thế bằng khối hình tiếp theo.  <br />
- Bảng thông số: Lần lượt là Line (lưu trữ số dòng đã hoàn thành), Score (điểm hiện tại), Level (đại lượng tượng trưng cho speed).  <br />
- Next Tetrads: Thông tin về các khối hình sinh kế tiếp.  <br />
 
Khi người chơi thua sẽ xuất hiện 1 bảng tổng sắp cho biết điểm số của người chơi và các kỷ lục trước<br />
![image](https://user-images.githubusercontent.com/94885088/170225487-e925c20a-9590-4f1c-b612-2162e0d048d3.png)Người chơi có thể bấm nút Replay để chơi lại hoặc Return để quay lại màn hình chính.<br />
### 2. Chức năng Battle <br />
Cũng là chơi nhưng mà chơi hai người. Mỗi bên điều khiển một phía của bàn phím. <br />
![image](https://user-images.githubusercontent.com/94885088/169710291-548f96b8-1293-421b-9476-129dd74ed5df.png)

Khi một trong hai người chơi thua cuộc, người còn lại sẽ chiến thắng.<br />
Nếu cả hai đều thua cuộc sẽ dựa trên điểm số quyết định người chiến thắng.<br />

![image](https://user-images.githubusercontent.com/94885088/170225290-eb2ffe56-4c28-4f01-bb13-ed142b99dc29.png)
### 3. Chức năng Setting <br />
Cho phép thiết lập các thông số của trò chơi bằng chuột, bao gồm:
- bật tắt Ghost Tetromino  <br />
![image](https://user-images.githubusercontent.com/94885088/170225806-ac546811-eee9-4ff7-a80c-999a9dd7a5c0.png)
- bật tắt Sound Efects  <br />
- điều chỉnh Music Volume <br />
- thiết lập Level. <br />

Ngoài ra còn reset Ranking Score và reset Settings. <br />
![image](https://user-images.githubusercontent.com/94885088/169710316-90c18edd-0bef-4967-981f-455d545b4f18.png)

### 4. Chức năng Help <br />
Chứa thông tin cụ thể về trò chơi: 
- Cách chơi (Helps) <br />
- Thông tin chi tiết (About) <br />
- Bản quyền (copyright) <br />
 ### 5. Một số chức năng khác <br />
- Đang chơi có thể bấm P để dừng hoặc chơi tiếp.<br />
- Độ khó trò chơi dựa vào điểm người chơi (hoặc thiết lập độ khó trong Settings).<br />
- Dữ liệu Ranking Score và User Settings được lưu trữ tại file Binary trong thư mục "settings" <br />

* <a name="tech"/>
## 4. Kỹ thuật lập trình <br />
### Xây dựng trên nền tảng C++ và SDL2 bao gồm:<br />
- SDL_Mixer: Hỗ trợ xử lý âm thanh. <br />
- SDL_Ttf: Hỗ trợ xử lý fonts chữ. <br />
- Các thư viện mở rộng C++. <br />
- IDE Visual Code. <br />

### Các kỹ thuật lập trình <br />
- Gồm tất cả các kỹ thuật cơ bản: <br />
- Biến (static, extern), vòng lặp, cấu trúc rẽ nhánh, mảng, chuỗi. <br />
- Con trỏ, set, map, vector <br />
- Class: Tạo, hủy, member function. <br />
- Đọc viết file binary. <br />
- Multithreading: Xử lý chức năng Battle.<br />
- Tách file giấu code.<br />
- Kỹ thuật duyệt mảng, sinh số ngẫu nhiên.<br />
- Kỹ năng refac code.
- Các kỹ thuật, syntax của SDL.
- Kỹ thuật giải phóng bộ nhớ động. <br />


### Ứng dụng
- Thuật toán sinh Khối Hình ngẫu nhiên giảm tỷ lệ sinh 2 khối giống nhau liên tiếp. <br />
- Mỗi chức năng của game (Play Single, Battle, Setting, Helps), mỗi Khối hình (Tetrads) được xác định bằng 1 đối tượng (class) riêng biệt.  <br />
- Ứng dụng đa nhiệm xử lý Battle khi có 2 người chơi cùng thao tác trên một bàn phím cùng 1 lúc.  <br />

- <a name="future"/>
## 5. Các hướng đi trong tương lai <br />
### Kết nối hóa trò chơi: Royal Battle: Nâng cấp chức năng Battle trở thành Royal Battle:<br />
- Sử dụng kết nối mạng máy tính (LAN, Router,... ) kết nối người chơi với nhau. <br />
- Sẽ thiết lập một trường cơ sở dữ liệu (database) lưu trữ trên máy chủ (server) lưu trữ thông tin người chơi. <br />
- Một Đấu Trường bao gồm khoảng 10-50-100 người chơi. <br />
- Khi một người chơi bất kỳ ăn hàng, hàng đó sẽ không biến mất mà trở thành Garbage Tetrads xuất hiện tại màn hình của người chơi khác bất kỳ (random). <br />
- Người chơi cuối cùng nằm xuống là người chiến thắng. <br />

 ### Xã hội hóa: Ứng dụng trí tuệ nhân tạo viết bot Deep Green chơi với người tự kỷ, người cô đơn,... <br />
 - Thêm chức năng chơi với máy (Play With Deep Green). <br />
 - Công việc của Deep Green:  <br />
&nbsp; - Nhận diện grid, nhận diện Khối Hình hiện tại và các khối tiếp theo <br />
&nbsp; - Xử lý dữ liệu bằng thuật toán. <br />
&nbsp; - Đưa ra vị trí và góc quay tối ưu nhất để bạn không bao giờ thắng được máy =))). <br />

### Tư bản hóa trò chơi: Hệ thống nạp tiền Pay to Play: <br />
- Người chơi sẽ nạp tiền vào game, số tiền sẽ chuyển vào tài khoản nhà phát hành. <br />
- Tiền nạp sẽ chuyển hóa thành Coin với tỷ lệ tương ứng. <br />
- Có thể dùng Coin để đổi các vật phẩm sau: <br />

&nbsp; - Skin cho Khối Hình theo cơ chế gacha (quay ngẫu nhiên từ một tập có sẵn) <br />
&nbsp; - Theme UI game mới <br />
&nbsp; - Theme Music game mới <br />
&nbsp; - Tốn Coin để giảm độ khôn của Deep Green, giúp chiến thắng bot một cách dễ dàng, giảm đi áp lực cuộc sống. <br />

* <a name="summary"/>
## 6. Kết luận
Game được viết do bản thân 100%, có sự học hỏi từ lazyfoo. <br />
### Việc hoàn thiện 1 dự án lập trình như thế này giúp em mở mang kiến thức rất nhiều.<br />
- Hiểu được mô hình phát triển 1 phần mềm kiểu thác nước: Phân tích, thiết kế, lập trình, kiểm thử, chuyển giao và bảo trì (forever). <br />
- Sử dụng thành thạo class, pointer, chia tách file,...<br />
- Cách dùng github.<br />
- Học rất nhiều syntax, thuật toán mới của c++.<br />
- Hiểu sơ sơ một số khía cạnh của lập trình hướng đối tượng: kế thừa, đa hình,...<br />
- Hình thành tư duy xử lý và giải quyết bài toán<br />


### Khuyết điểm <br />
- Code chưa được tối ưu hoàn toàn. <br />
- Các syntax và thuật toán vẫn còn ngây ngô. <br />
- Chưa refac code đến nơi đến chốn. <br />
- Một vài đoạn code thiếu trong sáng gây hoang mang cho người đọc <br />
- Nhưng với các kỹ thuật lập trình, tính chất trò chơi (chất lượng đồ họa, âm thanh, mechanics) đã trình bày bên trên em nghĩ mình xứng đáng được 10 môn này. (Nhưng nếu thấp hơn thì em vẫn vui vẻ chấp nhận ạ ^^). <br />

Cuối cùng, em xin chân thành cảm ơn bố mẹ, các thầy cô và các bạn đã đồng hành cùng em trong suốt chặng đường qua để em có thể tạo nên một trò chơi thật tuyệt vời, thú vị và đẳng cấp như thế này. Game rất hay, em chơi rất nhiều <br />
A Special Thanks To:<br />
- Thầy Trần Quốc Long.<br />
- Thầy Nguyễn Việt Anh.<br />
- Thầy Đỗ Minh Khá.<br />
- Và các bạn lớp INT2215 1.<br />
## Em xin trân trọng cảm ơn thầy cô đã dành thời gian lắng nghe. <br />
