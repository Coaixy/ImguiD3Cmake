#include <Windows.h>
#include <cstdint>
#include <vector>
#include <iostream>
class Memory
{
public:
	Memory(char* gameWindowName);

	template<typename var>
	bool write_mem(IN int64_t address, IN var value);

	template<typename var>
	var read_mem(IN int64_t address);

	DWORD GetProcessId(const char* Title);

	bool isAddressInMemoryRegions(IN int64_t address);

	int64_t FindPointer(IN int64_t baseAddress, IN std::vector<int64_t> offsets);
private:
	char* gameWindowStr = "";
	HANDLE processHandle;
	int pid;
	HWND hwnd;
	static RECT WindowRectangle;
};
template <typename var>
bool Memory::write_mem(IN int64_t address, IN var value) {
	return WriteProcessMemory(processHandle, (LPVOID)address, &value, sizeof(var), NULL);
}

template <typename var>
var Memory::read_mem(IN int64_t address) {
	if (test == 1)printf("%ld - test read \n", address);
	var value;
	ReadProcessMemory(processHandle, (LPCVOID)address, &value, sizeof(var), NULL);
	return value;
}

DWORD Memory::GetProcessId(const char* Title)
{
	HWND hWnd = FindWindow(NULL, Title);
	DWORD pid = 0;
	if (hWnd)
	{
		GetWindowThreadProcessId(hWnd, &pid);
	}
	this->pid = pid;
	this->hwnd = hWnd;
	return pid;
}

bool Memory::isAddressInMemoryRegions(IN int64_t address) {
	MEMORY_BASIC_INFORMATION info;
	VirtualQueryEx(processHandle, (LPCVOID)address, &info, sizeof(info));
	return info.State == MEM_COMMIT;
}

int64_t Memory::FindPointer(IN int64_t baseAddress, IN std::vector<int64_t> offsets)
{
	if (offsets.size() == 0) {
		return NULL;
	}

	int64_t Address = baseAddress;
	Address = read_mem<long>(Address);


	for (int i = 0; i < offsets.size(); i++) //Loop trough the offsets
	{
		Address += offsets[i];
		Address = read_mem<long>(Address);
	}
	return Address;
}


Memory::Memory(char* gameWindowName) {
	this->gameWindowStr = gameWindowName;
	this->GetProcessId(gameWindowStr);
	this->processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	GetWindowRect(hwnd, &this->WindowRectangle);
}