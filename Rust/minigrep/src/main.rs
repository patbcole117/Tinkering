use std::env;
use std::process;
use minigrep::Config;

fn main() {
    let argv: Vec<String> = env::args().collect();
    //dbg!(argv);
    let config = Config::build(&argv).unwrap_or_else(|err| {
        eprintln!("[!] argv is invalid: {err}");
        process::exit(1);
    });
    //dbg!(config);
    if let Err(err) = minigrep::run(config) {
        eprintln!("[!] error: {err}");
        process::exit(1);
    }
}
