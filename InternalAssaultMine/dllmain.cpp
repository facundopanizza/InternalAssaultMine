// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "helpers.h"

DWORD WINAPI mainLoop(HMODULE hModule) {
    uintptr_t moduleAddr = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    uintptr_t* playerAddr = (uintptr_t*)(moduleAddr + 0x10f4f4);

    uintptr_t* healthAddr = (uintptr_t*)(*playerAddr + 0xF8);
	uintptr_t* armorAddress = (uintptr_t*)(*playerAddr + 0xFC);
    uintptr_t* ammoAddress = (uintptr_t*)helpers::findDMA((uintptr_t)playerAddr, { 0x374, 0x14, 0x0 });

    bool bHealth = false, bArmor = false, bAmmo = false;

    while (true) {
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            break;
        }

        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            bHealth = !bHealth;
        }

        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            bArmor = !bArmor;
        }

        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            bAmmo = !bAmmo;
        }

        if (bHealth) {
            *healthAddr = 1337;
        }

        if (bArmor) {
            *armorAddress = 999;
        }

        if (bAmmo) {
            *ammoAddress = 10;
        }

        Sleep(10);
    }

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)mainLoop, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

