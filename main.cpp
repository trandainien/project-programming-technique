#include "functions.h"

int main()
{
    Node *pHead = nullptr;
    ExtractInfoFromCSVFileAndTurnToSLL(pHead);
    loginSection(pHead);

    //  bool ok = checkAccAndPass(account, password);
    delete[] pHead;
}