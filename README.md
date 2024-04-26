# Bài tập lớn - Cat & Sawblades (INT2215-50)

## Giới thiệu

* Họ và tên: Vũ Văn Mạnh
* Mã số sinh viên: 23020109
* Lớp K68CB, trường Đại học Công nghệ, Đại học Quốc gia Hà Nội
Cat & Sawblades là một tựa game Arcarde hành động. Trong game, bạn sẽ được hóa thân thành một con mèo né, tránh, nhảy qua những lưỡi cưa sắc bén để cố gắng sống sót lâu nhất có thể.

## Các tính năng của Cat & Sawblades:
- Có hệ thống tính điểm
- Nhịp độ game nhanh, buộc người chơi phải chơi liên tục
- Âm nhạc 8-bit
- Game càng chơi sẽ càng khó

## Hướng dẫn tải và chạy game (Video có hướng dẫn chi tiết)
### a, Cách 1: Không bao gồm code.
Tải game (được nén thành file .rar) [tại đây](https://drive.google.com/file/d/1Al9ILO8jCIFRANtA5SWQUSE3YVGAesUg/view?usp=sharing). Sau đó giải nén game vào một thư mục và bật Cat & Sawblades.exe để chơi.
### b, Cách 2: Bao gồm code và có thể biên dịch.
- Bước 1: Bấm vào phần "Code" màu xanh lá ở trên rồi bấm "Download ZIP" để tải
- Bước 2: Giải nén ra một thư mục
- Bước 3: Mở file "Cat & Sawblades.sln" bằng Visual Studio
- Bước 4: Chuột phải vào "Cat & Sawblades" ở góc trái trên màn hình mà ấn vào properties.
- Bước 5: Tại phần "VC++ Directories". Chỉnh đường dẫn "Include Directories" thành đường dẫn vào thư mục "...\SDL2\include" trong file game và đường dẫn "Library Directories" thành đường dẫn vào thư mục "...\SDL2\lib"
- Bước 6: Tại phần "C/C++", phần "General", chỉnh đường dẫn ""Additional Include Directories" thành đường dẫn vào thư mục "...\SDL2\include"
- Bước 7: Tại phần "Linker", phần "General", chỉnh đường dẫn "Additional Library Directories" thành đường dẫn vào thư mục "...\SDL2\lib\x64"
- Bước 8: Ấn Apply và OK. Ấn nút "Local Windows Debugger" hoặc F5 để chạy game 
## Chi tiết về game
### Gameplay
Demo game tại đây
### Control

- Di chuyển nhân vật bằng phím mũi tên
- Ấn nút Esc để mở menu (Không pause)
### Nội dung game
Người chơi phải di chuyển và nhảy để né, tránh các lưỡi cưa. Nếu người chơi nhảy qua lưỡi cưa và chạm đất, lưỡi của sẽ biến mất và người chơi được cộng điểm. Nếu người chơi chạm vào lưỡi cưa, lượt chơi sẽ kết thúc
### Một số hình ảnh trong game

## Các kỹ thuật lập trình đã sử dụng
- Vòng lặp
- Mảng tĩnh, vector
- Xâu
- Con trỏ
- Lập trình hướng đối tượng
- Làm việc với file
- Xử lý va chạm
- SDL2 (SDL2_image, SDL2_mixer, SDL2_ttf)
- Kỹ thuật Texture font, mouse event, key event
- Kỹ thuật sử dụng hoạt ảnh (Sprites)
- Sound effects và Music
- Kỹ thuật hit-box
- Kỹ thuật deltaTime và cap FPS

## Về source code của game
- globals.hpp: Khai báo các biến toàn cục như FPS, Resolution, Spawning rate, Volume, ...
- cat.cpp và Cat.hpp: Quản lý nhân vật chính như lực nhảy, tốc độ, animation, ...
- deathmenu.cpp và Deathmenu.hpp: Quản lý cửa sổ khi game over
- entity.cpp và Entity.hpp: Quản lý màn hình của game
- LTimer.cpp và LTimer.hpp: Đo frame giữa các khung hình để tính FPS trung bình
- mainMenu.cpp và MainMenu.hpp: Quản lý màn hình chính của trò chơi
- sawblade.cpp và Sawblade.hpp: Quản lý lưỡi cưa như tốc độ, độ lớn, ...
- renderwindow.cpp và RenderWindow.hpp: Dùng để load hoặc render các texture lên màn hình chơi
- main.cpp: Hàm main của game
