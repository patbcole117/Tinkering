fn main() {
    let mut items = vec!["Zero", "One", "Two", "Three", "Four", "Five"];
    println!("[+] {:?}", items);

    println!();
    println!("[+] Printing items by index.");
    for i in 0..items.len() {
        println!("{i}: {}", items[i]);
    }

    println!();
    println!("[+] Printing items by item.");
    for item in items.iter() {
        println!("{item}");
    }

    println!();
    println!("[+] Pushing Six and Seven.");
    for i in vec!["Six", "Seven"].iter() {
        items.push(i);
    }
    println!("[+] {:?}", items);

    println!();
    println!("[+] Replacing with digits.");
    for i in items.iter_mut() {
        *i = match *i {
            "One" => "1",
            "Two" => "2",
            _ => *i,
        }
    }
    println!("[+] {:?}", items);

    println!();
    println!("[+] Removing index of '1' and '2' using overwrite + pop method.");
    let mut idx = 0;
    for i in 0..items.len() {
        if items[i].len() > 1 {
            items[idx] = items[i];
            idx += 1;
        }
    }
    for _ in 0..(items.len() - idx) {
        items.pop();
    }
    println!("[+] {:?}", items);

    println!();
    println!("[+] Removing \"Five\" and \"Zero\" and \"Seven\" with reverse swap_remove method.");
    for i in (0..items.len()).rev() {
        if items[i] == "Five" || items[i] == "Zero" || items[i] == "Seven" {
            items.remove(i);
        }
    }
    println!("[+] {:?}", items);
}
