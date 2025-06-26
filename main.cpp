// #include "client.h"
// #include <QCoreApplication>
// #include <QTextStream>
// #include <iostream>

// int main(int argc, char *argv[])
// {
//     QCoreApplication a(argc, argv);

//     client client;
//     QObject::connect(&client, &client::connected, [](){
//         qDebug() << "Connection established!";
//     });

//     client.startConnection("127.0.0.1", 50000);

//     QTextStream input(stdin);
//     while(true) {
//         std::cout << "Enter message (or 'exit' to quit): ";
//         QString message = input.readLine();
//         if(message == "exit") break;
//         client.sendMessage(message);
//     }

//     return a.exec();
// }
#include <QApplication>
#include "SigninWindow.h"  // فرض می‌کنیم کلاس بالا در فایل جدا به نام SigninWindow.h و .cpp هست
#include "forgotpswwindow.h" // در بالای main.cpp اضافه کنید
#include"menuwindow.h"
#include"signupwindow.h"
#include"editwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   ///SigninWindow w;
    //Forgotpswwindow w;
    //Menuwindow w;
    Editwindow w;
    w.show();

    return a.exec();
}
