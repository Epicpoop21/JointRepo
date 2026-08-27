$files = Get-ChildItem -Recurse -Include *.cpp, *.h | 
         Where-Object { $_.FullName -notmatch "\\dependencies\\" -and $_.FullName -notmatch "\\imgui\\"}
$total = 0
foreach ($file in $files) {
    $lineCount = (Get-Content $file.FullName).Count
    $total += $lineCount
    Write-Host "$($file.FullName): $lineCount lines"
}
Write-Host "-------------------------------"
Write-Host "Total lines of code: $total"
Read-Host "Press ENTER to exit"