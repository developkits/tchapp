#include "TchErrorHandler.h"
#include <stdio.h>
#ifdef OS_WIN
#include <Windows.h> 
#endif // OS_WIN

namespace Tnelab{
	TchErrorHandler::TchErrorDelegate TchErrorHandler::_tch_error_delegate = 0;
	void TchErrorHandler::OnTchError(int error_code, std::string error_msg) {
		if (_tch_error_delegate != 0) {
			_tch_error_delegate(error_code, error_msg);
			return;
		}
#ifdef OS_WIN
		if (!error_msg.empty()) {
			// ����������Ϣ��ԭ��ʹ��AllocConsole���ǵ����Ŀ���̨���ڲ��ܵ����ر�
			char msg[1024] = { 0 };
			sprintf(msg, "TCH_ERROR:%d,%s\r\n", error_code, error_msg.c_str());
			MessageBoxA(NULL, error_msg.c_str(), "Error, press Ctrl+C to copy the details", MB_ICONERROR | MB_OK);
		}
#else
		if (!error_msg.empty())	printf("TCH_ERROR:%d,%s\n", error_code, error_msg.c_str());
#endif // OS_WIN				
	}
	int TchErrorHandler::SetTchErrorDelegate(TchErrorDelegate delegate) {
		_tch_error_delegate = delegate;
		return 0;
	}
}