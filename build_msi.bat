@echo off
candle -arch x64 Code\ShellExtension\MSI\RPFXplorer.wxs 
light -ext WixUIExtension -cultures:en-us RPFXplorer.wixobj -out bin\RPFXplorer.msi

del RPFXplorer.wixobj

@pause
