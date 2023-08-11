function fEnd-Process{
    <#
    .SYNOPSIS
        Ends a process based on a given string.

    .DESCRIPTION
        fEnd-Process is a function that will locate a process based on a given string and attempt to close the process.

    .EXAMPLE
        fEnd-Process firefox

        fEnd-Process firefox spotify
    
    .INPUTS
        System.String
    
    .OUTPUTS
        None.

    .NOTES
        Author: Pat
        Date Created: 2022/11/22
        Date Modified:2022/11/22
    #>

    foreach ($a in $args){
        Get-Process $a | % {$_.CloseMainWindow()}
    }

}