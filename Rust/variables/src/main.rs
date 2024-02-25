const THREE_HOURS_IN_SECONDS: u32 = 60 * 60 * 3;

fn main() {
    let mut x = THREE_HOURS_IN_SECONDS;
    println!("The value of x is: {x}");
    x = 6;
    println!("The value of x is: {x}");
    shadow();
    floats();
}

fn shadow() {
    let x = 5;
    let x = x + 1;
    {
        let x = x * 2;
        println!("The value of x in the inner scope is: {x}");
    }
    println!("The value of x in the outer scope is {x}");
}

fn floats() {
    let q = 56.7 / 32.2;
    println!("The value of q is {q}");

    let r = 56.7 % 32.2;
    println!("The value of r is {r}");

    let a = q * 32.2;
    println!("The value of a is {a}");
}

fn param(x: i32){
    println!("The value of param is {param}");
}
