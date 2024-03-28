fn main() {
    let mut s = String::from("Patrick");
    let x = &s;
    s.pop();
    println!("[+] {x}");
}
