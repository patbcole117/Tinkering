function fGrab-Many {
    <#
    .SYNOPSIS
        Searches for files and copies them to a destination directory.

    .DESCRIPTION
        fGrab-Many is a function that will search recursively for any files matching a particular pattern and 
        then wil copy those files to a user-specified destination folder. fGrab-Many can be given multiple 
        patterns to match. fGrab-Many will create a CSV manifest file in the destination location. Ran with no 
        parameters, fGrab-Many will copy everything (excluding directories) in .\ and place copies of the files 
        into .\deviouslicks\.

    .EXAMPLE
        fGrab-Many

    .EXAMPLE
        fGrab-Many -Source C:\Users\Bob\Documents\ -Destination .\ -Include *.txt,*.png

    .EXAMPLE
        fGrab-Many -Attribute Directory -Output C:\output.csv
    
    .INPUTS
        System.String, System.String[]
    
    .OUTPUTS
        None.

    .NOTES
        Author: Pat
        Date Created: 2022/11/22
        Date Modified:2022/11/22
    #>

    param(
        
        [String]
        $SourceDir = ".\",

        [String]
        $DestinationDir = "C:\deviouslicks\",

        [String[]]
        $Include,

        [String[]]
        $Exclude,

        [String]
        $Output = "$DestinationDir\__fgrab-log.csv",

        [String]
        $Attribute = "!Directory"

    )

    New-Item $DestinationDir -Type Director -ErrorAction SilentlyContinue
    
    Write-Host "############################################################
    SOURCE - $SourceDir
    DESTINATION - $DestinationDir
    INCLUDE - $Include
    EXCLUDE - $Exclude
    OUTPUT - $Output`n############################################################"

    Get-ChildItem -Force -Recurse -Path $SourceDir -Include $Include -Exclude $Exclude -Attributes $Attribute |
        Where-Object {$_.FullName -notlike "$DestinationDir*"} |
            ForEach-Object{
                $SourceFile=$_.FullName
                $DestinationFile=$DestinationDir + $_.Name
                if(Test-Path $DestinationFile){
                    $i=0
                    while(Test-Path $DestinationFile){
                        $DestinationFile = "{0}{1}{2}{3}{4}" -f $DestinationDir, $_.BaseName, "-", $i++, $_.Extension
                    }
                }
                $_ | Export-Csv -Path $Output -Append -NoTypeInformation
                Copy-Item -Path $SourceFile -Destination $DestinationFile -Force
            }
}