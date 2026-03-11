$path = 'c:\Users\Виктор\Desktop\ogo\alkad src\invis\core\main\other.hpp'
$content = [System.IO.File]::ReadAllText($path, [System.Text.Encoding]::GetEncoding("windows-1251"))
$content = $content.Replace("void validatemanipulatorpos(float maxxzmanipulator, float maxymanipulator)`r`n{", "void validatemanipulatorpos(float maxxzmanipulator, float maxymanipulator)`r`n{`r`n`tif (target_ply == nullptr) return;")
[System.IO.File]::WriteAllText($path, $content, [System.Text.Encoding]::UTF8)
