$scriptpath = Split-Path ($MyInvocation.MyCommand.Path) -Parent

$filelist = @()

for($i=0;$i -lt 100;$i++) {
    # get random data 1K in size
    $limit=1024
    $a = ""
    for($y=0;$y -lt $limit;$y++)    {
        $a=$a+[char][byte]((Get-Random 64)+32)
    }

    $filename = join-path $scriptpath ”testfile_$((Get-Random 100000).tostring()).txt”
    $a | Out-File -FilePath $filename
    $filelist += $filename
}

$filelist | Out-File (join-path $scriptpath "filelist.txt")
