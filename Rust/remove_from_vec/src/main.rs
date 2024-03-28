fn main() {
    use std::time::Instant;
    let vec: Vec<u32>  = (0..=100000).collect();

    let now = Instant::now();
    {
        for _ in 0..1000 {
            reverse_swap_remove(vec.clone());    
        }
    }
    let elapsed = now.elapsed();
    println!("[+]{:.2?} reverse_swap_remove", elapsed);
    
    let now = Instant::now();
    {
        for _ in 0..1000 {
            overwrite_pop_method(vec.clone());    
        }
    }
    let elapsed = now.elapsed();
    println!("[+]{:.2?} overwrite_pop_method", elapsed);

    let now = Instant::now();
    {
        for _ in 0..1000 {
            reverse_remove(vec.clone());    
        }
    }
    let elapsed = now.elapsed();
    println!("[+]{:.2?} reverse_remove", elapsed);


    }
// Remove every 5th item.
fn overwrite_pop_method(mut items: Vec<u32>) {
    let mut idx = 0;

    for i in 0..items.len() {
        if i % 3 != 0 {
            items[idx] = items[i];
            idx += 1;
        }
    }
    for _ in 0..(items.len()-idx) {
        items.pop();
    }
    //println!("[+] {:?}", items);
}

fn reverse_remove(mut items: Vec<u32>) {
    for i in (0..items.len()).rev() {
        if i % 3 == 0 {
            items.remove(i);
        }
    }
}

fn reverse_swap_remove(mut items: Vec<u32>) {
    for i in (0..items.len()).rev() {
        if i % 3 == 0 {
            items.swap_remove(i);
        }
    }
}
