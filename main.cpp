#include "utilities/main_includes.h"
#include "src/ui/sign_screen/sign_screen.h"
#include "src/ui/replay_screen/replayscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // launch Main Screen
    // MainScreen M;
    // M.show();

    // launch Registeration screen
    SignScreen w;
    w.show();

    return a.exec();
}
