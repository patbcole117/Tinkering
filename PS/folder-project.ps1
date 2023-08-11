function fCreate-RandomFolders {

    param(
    [parameter(Mandatory)]
        $location
    )
  
    $num_f = Get-Random -Minimum 1 -Maximum 10

    for($i=1; $i -le $num_f; $i+=1){
        New-Item $location\FOLDER-$i -ItemType Directory
    }
}

function fDirgame-Recursive {
    
    param(
        [parameter(Mandatory)]
        $depth,

        [parameter(Mandatory)]
        $trail
    )

    Write-Output $trail
    Write-Output $depth

    if($depth -ge 0){
        fCreate-RandomFolders $trail
        $depth = $depth - 1
        Get-ChildItem $trail |  ForEach-Object{fDirgame-Recursive $depth $_.FullName}
        #Start-Sleep 2
    }

    $depth = 2
}

function fStart-Dirgame {
    
    param(
        [parameter(Mandatory)]
        $depth
    )

    new-Item ".\dirgame" -Type Directory
    fDirgame-Recursive $depth ".\dirgame"
}