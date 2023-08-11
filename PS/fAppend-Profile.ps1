function fAppend-Profile{
    <#
    .SYNOPSIS
        Appends a given string to the end of $profile.CurrentUserAllHosts.

    .DESCRIPTION
        fAppend-Profile is a function that will append a string to 
        $PROFILE.CurrentUserAllHosts. fAppend-Profile uses Out-File with utf8 encoding 
        by default.

    .EXAMPLE
        fAppend-Profile -Strings "Set-Alias...","Set-Alias..." -Encoding utf8
    
    .INPUTS
        System.String[]
    
    .OUTPUTS
        None.

    .NOTES
        Author: Pat
        Date Created: 2022/11/20
        Date Modified:2022/11/20
    #>

    param(
        [Parameter(Mandatory)]
        [String[]]$Strings,

        [Parameter()]
        [String]$Location = $PROFILE.CurrentUserAllHosts,

        [Parameter()]
        [String]$Encoding = "utf8"
    )

    foreach($str in $Strings){
        $str | Out-File -FilePath $Location -Encoding $Encoding -Append
    }
}