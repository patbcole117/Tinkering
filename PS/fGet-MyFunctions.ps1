function fGet-MyFunctions{
    <#
    .SYNOPSIS
        Gets my functions.

    .DESCRIPTION
        fGet-MyFunctions is a function that will retrieve all functions whose name is of the form <f.*-.*>. Since
        my functions are all created with the name f... it will only retrieve functions I have created.

    .EXAMPLE
        fGet-MyFunctions
    
    .INPUTS
        None.
    
    .OUTPUTS
        None.

    .NOTES
        Author: Pat
        Date Created: 2022/11/22
        Date Modified:2022/11/22
    #>

    dir function:\* | Out-String -Stream | Select-String -Pattern f.*-.* -CaseSensitive
}