function fEdit-Profile {

    <#
    .SYNOPSIS
        Opens $PROFILE.CurrentUserAllHosts in Notepad.

    .DESCRIPTION
        fEditProfile is a function that will open $PROFILE.CurrentUserAllHosts in Notepad.

    .EXAMPLE
        fEdit-Profile
    
    .INPUTS
        None.
    
    .OUTPUTS
        None.

    .NOTES
        Author: Pat
        Date Created: 2022/11/22
        Date Modified:2022/11/22
    #>
    notepad $PROFILE.CurrentUserAllHosts
}