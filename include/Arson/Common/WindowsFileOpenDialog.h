#ifndef ARSON_FILE_DIALOGUE_H
#define ARSON_FILE_DIALOGUE_H

#include <windows.h>
#include <shobjidl.h>

namespace Arn
{
	//Opens a File Dialog and Returns a wstring
	//fileFilters formatted as ' L"*.jpg;*.jpeg" '
	std::wstring WindowsFileOpenDialog(LPCWSTR fileFilters = L"*")
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			IFileOpenDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
				IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			COMDLG_FILTERSPEC rgSpec[] = { {L"", fileFilters} };
			pFileOpen->SetFileTypes( 1,rgSpec );

			if (SUCCEEDED(hr))
			{
				// Show the Open dialog box.
				hr = pFileOpen->Show(NULL);
				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						pItem->Release();
						return pszFilePath;
					}
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}
		return L"";
	}
}

#endif