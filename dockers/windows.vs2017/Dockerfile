# escape=`
FROM cirrusci/windowsservercore:2019
LABEL maintainer="developers@moneymanagerex.org"
ARG wxVer=3.1.2
ARG wxURL=https://github.com/wxWidgets/wxWidgets/releases/download/v$wxVer/
ARG curlVer=7_64_1
ARG gettextURL=https://github.com/mlocati/gettext-iconv-windows/releases/download
ARG comp=141
ARG chocolateyUseWindowsCompression=false
ENV wxwin c:\wxWidgets-$wxVer
ENV CURL_ROOT=c:\curl-$curlVer
RUN setx path "c:\Python;c:\Python\Scripts;%path%;%ProgramFiles%\CMake\bin;c:\gettext\bin"
RUN cinst --no-progress -y `
      7zip.commandline `
      cmake `
      nsis `
      pkgconfiglite `
      visualstudio2017-workload-vctools `
 && cinst --no-progress -y python3 --params "/InstallDir:c:\Python" `
 && rmdir /q/s %TEMP%\chocolatey `
 && refreshenv `
 && pip install certifi `
 && pip install git+https://github.com/frerich/clcache.git `
 && rmdir /q/s "%LOCALAPPDATA%\pip\Cache" `
 && curl -fsL --fail-early `
      -O %gettextURL%/v0.19.8.1-v1.15/gettext0.19.8.1-iconv1.15-shared-64.zip `
 && 7z x -y "-oc:\gettext" gettext*.zip `
 && del /q/f/s gettext*.zip `
 && curl -fsL --fail-early `
      -O %wxURL%/wxWidgets-%wxVer%-headers.7z `
      -O %wxURL%/wxMSW-%wxVer%_vc%comp%_Dev.7z `
      -O %wxURL%/wxMSW-%wxVer%_vc%comp%_ReleaseDLL.7z `
      -O %wxURL%/wxMSW-%wxVer%_vc%comp%_x64_Dev.7z `
      -O %wxURL%/wxMSW-%wxVer%_vc%comp%_x64_ReleaseDLL.7z `
 && 7z x -y "-o%wxwin%" wx*-%wxVer%*.7z `
 && del /q/f/s wx*-%wxVer%*.7z `
 && git clone -q --depth=1 --branch=curl-%curlVer% https://github.com/curl/curl.git %CURL_ROOT%-src `
 && cmake -T v%comp%,host=x64 -G "Visual Studio 15 2017 Win64" `
      -DBUILD_CURL_EXE=OFF `
      -DBUILD_SHARED_LIBS=OFF `
      -DCURL_DISABLE_LDAP=ON `
      -DCURL_DISABLE_LDAPS=ON `
      -DCURL_DISABLE_TELNET=ON `
      -DCURL_DISABLE_DICT=ON `
      -DCURL_DISABLE_FILE=ON `
      -DCURL_DISABLE_TFTP=ON `
      -DCURL_DISABLE_RTSP=ON `
      -DCURL_DISABLE_POP3=ON `
      -DCURL_DISABLE_IMAP=ON `
      -DCURL_DISABLE_SMTP=ON `
      -DCURL_DISABLE_GOPHER=ON `
      -DENABLE_MANUAL=OFF `
      -DCMAKE_USE_WINSSL=ON `
      -DBUILD_TESTING=OFF `
      -DCMAKE_INSTALL_PREFIX=%CURL_ROOT% `
      -S %CURL_ROOT%-src -B %CURL_ROOT%-src\build `
 && cmake --build %CURL_ROOT%-src\build --target install --config Release `
      -- /maxcpucount /verbosity:minimal /nologo /p:PreferredToolArchitecture=x64 `
 && rmdir /q/s %CURL_ROOT%-src
