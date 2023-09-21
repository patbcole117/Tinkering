package main
import (
    "fmt"
    "os"
    "strings"
    "github.com/c-bata/go-prompt"
)

func completer(d prompt.Document) []prompt.Suggest {
    args := strings.Split(d.TextBeforeCursor(), " ")
    if len(args) <=1 {
        return prompt.FilterHasPrefix(rootOpts, d.GetWordBeforeCursor(), true)
    }
    
    first := args[0]
    switch first {
    case "agents":
        second := args[1]
        if len(args) == 2{
            return prompt.FilterHasPrefix(agentsOpts, second, true)
        }
        third := args[2]
        if len(args) == 3{
            return prompt.FilterHasPrefix(agentOpts, third, true)
        }
        
    case "nodes":
    case "exit":
    }
    return prompt.FilterHasPrefix(rootOpts, d.GetWordBeforeCursor(), true)
}

func main() {
    for {
        fmt.Println("Please select table.")
        t := prompt.Input("> ", completer)
        if t == "exit" {
            os.Exit(1)
        }
        fmt.Println("You selected " + t)
    }
}

var rootOpts = []prompt.Suggest{
    {Text: "agents"},
    {Text: "nodes"},
    {Text: "exit"},
}

var agentsOpts = []prompt.Suggest{
    {Text: "one"},
    {Text: "two"},
    {Text: "three"},
}

var agentOpts = []prompt.Suggest{
    {Text: "do"},
    {Text: "logs"},
    {Text: "jobs"},
}
