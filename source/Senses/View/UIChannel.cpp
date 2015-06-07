



int UIMain()
{
    auto message_dump= []() -> int {
    MSG msg;
    // Main message loop:
      while (GetMessage(&msg, NULL, 0, 0))
      {
      TranslateMessage(&msg);
          DispatchMessage(&msg);
      }
    return (int) msg.wParam;
  };
}

