#include "common.h"
#include "payload.h"
#include "internals.h"
#include "patch.h"
#include "chrome.h"

f_DbgPrintEx DbgPrintEx;
FILE* logfile;
bool is_stdout;

//typedef void* (*f_memcpy)(void* dest, const void* src, size_t len);
//extern f_memcpy pRealMemcpy;

void init() {
	//pRealMemcpy = GetProcAddress(LoadLibraryA("ntdll.dll"), "memcpy");

	//DbgPrintEx = (f_DbgPrintEx)GetProcAddress(LoadLibraryA("ntdll"), "DbgPrintEx");
	if (fopen_s(&logfile, "C:\\Users\\niklas\\chrome_hacks\\payload_log.txt", "a")) {
		logfile = stdout;
		is_stdout = true;
	}
}

void cleanup() {
	if (!is_stdout)
		fclose(logfile);
}

bool inner() {
	PROP(patch_chrome());
}

void payload(volatile context* ctx) {
	//__debugbreak();
	init();
	//__debugbreak();
	//DebugBreak();
	//*(volatile int*)0 = 1337;
	//MessageBoxA(0, "hi", "foo", 0);
	LOG("Started payload\n");
	inner();

	cleanup();
	//__debugbreak();
	for (;;) {
		Sleep(10000);
	}
}