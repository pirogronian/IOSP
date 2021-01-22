
#include <cassert>
#include <Utils/InputKeyBinder.h>

using namespace IOSP;

int main()
{
    InputKeyBinder binder;

    assert(binder.boundAction(5, true, true) == 0);
    assert(binder.actionKey(12) == 0);
    assert(binder.actionShift(12) == false);
    assert(binder.actionCtrl(12) == false);

    binder.bind(12, 5, true, true);
    assert(binder.boundAction(5, true, true) == 12);
    assert(binder.actionKey(12) == 5);
    assert(binder.actionShift(12) == true);
    assert(binder.actionCtrl(12) == true);

    binder.unbindAction(12);
    assert(binder.boundAction(5, true, true) == 0);
    assert(binder.actionKey(12) == 0);
    assert(binder.actionShift(12) == false);
    assert(binder.actionCtrl(12) == false);

    binder.bind(12, 5, true, true);
    assert(binder.boundAction(5, true, true) == 12);
    assert(binder.actionKey(12) == 5);
    assert(binder.actionShift(12) == true);
    assert(binder.actionCtrl(12) == true);

    binder.unbindKey(5, true, true);
    assert(binder.boundAction(5, true, true) == 0);
    assert(binder.actionKey(12) == 0);
    assert(binder.actionShift(12) == false);
    assert(binder.actionCtrl(12) == false);

    return 0;
}
