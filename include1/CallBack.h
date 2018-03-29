/*===========================================================================
	About
*/

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
		{
			return (INT_PTR)TRUE;
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDC_GITHUB:
				{
					ShellExecute(0, L"open", L"https://github.com/reznikovkg/kg-plot", 0, 0, SW_SHOWNORMAL);
					break;
				}
				case IDOK:
				{
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
					break;
				}
				case IDCANCEL:
				{
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
					break;
				}
				default: break;
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}

/*===========================================================================
	Help
*/

INT_PTR CALLBACK Help(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
		{
			return (INT_PTR)TRUE;
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK1:
				{
					EndDialog(hDlg, LOWORD(wParam));
					break;
				}
				case IDCANCEL:
				{
					EndDialog(hDlg, LOWORD(wParam));
					break;
				}
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}

/*===========================================================================
	Tuning
*/

INT_PTR CALLBACK Tuning(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		_GRID = true;
		_AXES = true;
		_NUMS = true;
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case IDC_GRID:
			{
				switch (HIWORD(wParam))
				{
					case BN_CLICKED:
					{
						if (SendDlgItemMessage(hDlg, IDC_GRID, BM_GETCHECK, 0, 0))
						{
							_GRID = true;
						} 
						else
						{
							_GRID = false;
						}
						break;
					}
				}
				break;
			}
			case IDC_AXES:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					if (SendDlgItemMessage(hDlg, IDC_AXES, BM_GETCHECK, 0, 0))
					{
						_AXES = true;
					}
					else
					{
						_AXES = false;
					}
					break;
				}
				}
				break;
			}
			case IDC_NUMS:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					if (SendDlgItemMessage(hDlg, IDC_NUMS, BM_GETCHECK, 0, 0))
					{
						_NUMS = true;
					}
					else
					{
						_NUMS = false;
					}
					break;
				}
				}
				break;
			}
			case IDOK:
			{
				if (SendDlgItemMessage(hDlg, IDC_GRID, BM_GETCHECK, 0, 0))
				{
					_GRID = true;
				}
				else
				{
					_GRID = false;
				}
				if (SendDlgItemMessage(hDlg, IDC_AXES, BM_GETCHECK, 0, 0))
				{
					_AXES = true;
				}
				else
				{
					_AXES = false;
				}
				if (SendDlgItemMessage(hDlg, IDC_NUMS, BM_GETCHECK, 0, 0))
				{
					_NUMS = true;
				}
				else
				{
					_NUMS = false;
				}
				
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
				break;
			}
			case IDCANCEL:
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
				break;
			}
			default: break;
		}
	}
	}
	return (INT_PTR)FALSE;
}

