use std::fs::File;
use std::io::{BufRead, BufReader, Write};

struct Array {
    data: Vec<i32>,
}

impl Array {
    fn new() -> Self {
        Array { data: Vec::new() }
    }

    fn push(&mut self, value: i32) {
        self.data.push(value);
    }

    fn del(&mut self, index: usize) {
        if index < self.data.len() {
            self.data.remove(index);
        }
    }

    fn get(&self, index: usize) -> i32 {
        if index < self.data.len() {
            self.data[index]
        } else {
            -1
        }
    }

    fn print(&self) {
        print!("Array (size={}): ", self.data.len());
        for val in &self.data {
            print!("{} ", val);
        }
        println!();
    }

    fn save(&self, filename: &str) {
        if let Ok(mut file) = File::create(filename) {
            let _ = writeln!(file, "ARRAY");
            let _ = writeln!(file, "{}", self.data.len());
            for val in &self.data {
                let _ = writeln!(file, "{}", val);
            }
        }
    }

    fn load(&mut self, filename: &str) {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let mut lines = reader.lines();
            
            if let Some(Ok(type_line)) = lines.next() {
                if type_line == "ARRAY" {
                    if let Some(Ok(size_line)) = lines.next() {
                        if let Ok(sz) = size_line.parse::<usize>() {
                            for _ in 0..sz {
                                if let Some(Ok(val_line)) = lines.next() {
                                    if let Ok(val) = val_line.parse::<i32>() {
                                        self.push(val);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

struct StackNode {
    value: i32,
    next: Option<Box<StackNode>>,
}

struct Stack {
    top: Option<Box<StackNode>>,
    size: usize,
}

impl Stack {
    fn new() -> Self {
        Stack { top: None, size: 0 }
    }

    fn push(&mut self, value: i32) {
        let node = Box::new(StackNode {
            value,
            next: self.top.take(),
        });
        self.top = Some(node);
        self.size += 1;
    }

    fn pop(&mut self) -> i32 {
        if let Some(node) = self.top.take() {
            self.top = node.next;
            self.size -= 1;
            node.value
        } else {
            -1
        }
    }

    fn peek(&self) -> i32 {
        if let Some(node) = &self.top {
            node.value
        } else {
            -1
        }
    }

    fn print(&self) {
        print!("Stack (size={}): ", self.size);
        let mut current = &self.top;
        while let Some(node) = current {
            print!("{} ", node.value);
            current = &node.next;
        }
        println!();
    }

    fn save(&self, filename: &str) {
        if let Ok(mut file) = File::create(filename) {
            let _ = writeln!(file, "STACK");
            let _ = writeln!(file, "{}", self.size);
            let mut current = &self.top;
            while let Some(node) = current {
                let _ = writeln!(file, "{}", node.value);
                current = &node.next;
            }
        }
    }

    fn load(&mut self, filename: &str) {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let mut lines = reader.lines();
            
            if let Some(Ok(type_line)) = lines.next() {
                if type_line == "STACK" {
                    if let Some(Ok(size_line)) = lines.next() {
                        if let Ok(sz) = size_line.parse::<usize>() {
                            let mut values = Vec::new();
                            for _ in 0..sz {
                                if let Some(Ok(val_line)) = lines.next() {
                                    if let Ok(val) = val_line.parse::<i32>() {
                                        values.push(val);
                                    }
                                }
                            }
                            for i in (0..values.len()).rev() {
                                self.push(values[i]);
                            }
                        }
                    }
                }
            }
        }
    }
}

struct ForwardNode {
    value: i32,
    next: Option<Box<ForwardNode>>,
}

struct ForwardList {
    head: Option<Box<ForwardNode>>,
    size: usize,
}

impl ForwardList {
    fn new() -> Self {
        ForwardList { head: None, size: 0 }
    }

    fn push(&mut self, value: i32) {
        let node = Box::new(ForwardNode {
            value,
            next: self.head.take(),
        });
        self.head = Some(node);
        self.size += 1;
    }

    fn del(&mut self, index: usize) {
        if index >= self.size || self.head.is_none() {
            return;
        }

        if index == 0 {
            if let Some(node) = self.head.take() {
                self.head = node.next;
                self.size -= 1;
            }
            return;
        }

        let mut current = &mut self.head;
        for _ in 0..index - 1 {
            if let Some(node) = current {
                current = &mut node.next;
            }
        }

        if let Some(node) = current {
            if let Some(mut temp) = node.next.take() {
                node.next = temp.next.take();
                self.size -= 1;
            }
        }
    }

    fn get(&self, index: usize) -> i32 {
        if index >= self.size {
            return -1;
        }
        let mut current = &self.head;
        for _ in 0..index {
            if let Some(node) = current {
                current = &node.next;
            }
        }
        if let Some(node) = current {
            node.value
        } else {
            -1
        }
    }

    fn print(&self) {
        print!("ForwardList (size={}): ", self.size);
        let mut current = &self.head;
        while let Some(node) = current {
            print!("{} ", node.value);
            current = &node.next;
        }
        println!();
    }

    fn save(&self, filename: &str) {
        if let Ok(mut file) = File::create(filename) {
            let _ = writeln!(file, "FORWARD");
            let _ = writeln!(file, "{}", self.size);
            let mut current = &self.head;
            while let Some(node) = current {
                let _ = writeln!(file, "{}", node.value);
                current = &node.next;
            }
        }
    }

    fn load(&mut self, filename: &str) {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let mut lines = reader.lines();
            
            if let Some(Ok(type_line)) = lines.next() {
                if type_line == "FORWARD" {
                    if let Some(Ok(size_line)) = lines.next() {
                        if let Ok(sz) = size_line.parse::<usize>() {
                            let mut values = Vec::new();
                            for _ in 0..sz {
                                if let Some(Ok(val_line)) = lines.next() {
                                    if let Ok(val) = val_line.parse::<i32>() {
                                        values.push(val);
                                    }
                                }
                            }
                            for i in (0..values.len()).rev() {
                                self.push(values[i]);
                            }
                        }
                    }
                }
            }
        }
    }
}

struct DoubleNode {
    value: i32,
    next: Option<Box<DoubleNode>>,
    prev: *mut DoubleNode,
}

struct DoublyList {
    head: Option<Box<DoubleNode>>,
    tail: *mut DoubleNode,
    size: usize,
}

impl DoublyList {
    fn new() -> Self {
        DoublyList {
            head: None,
            tail: std::ptr::null_mut(),
            size: 0,
        }
    }

    fn push(&mut self, value: i32) {
        let mut node = Box::new(DoubleNode {
            value,
            next: None,
            prev: self.tail,
        });

        let node_ptr = &mut *node as *mut DoubleNode;

        if !self.tail.is_null() {
            unsafe {
                (*self.tail).next = Some(node);
            }
        } else {
            self.head = Some(node);
        }

        self.tail = node_ptr;
        self.size += 1;
    }

    fn del(&mut self, index: usize) {
        if index >= self.size {
            return;
        }

        if index == 0 {
            if let Some(mut node) = self.head.take() {
                self.head = node.next.take();
                if let Some(next) = &mut self.head {
                    next.prev = std::ptr::null_mut();
                } else {
                    self.tail = std::ptr::null_mut();
                }
                self.size -= 1;
            }
            return;
        }

        let mut current_opt = &mut self.head;
        for _ in 0..index {
            if let Some(node) = current_opt {
                current_opt = &mut node.next;
            }
        }

        if let Some(mut node) = current_opt.take() {
            let prev_ptr = node.prev;
            *current_opt = node.next.take();

            if !prev_ptr.is_null() {
                unsafe {
                    (*prev_ptr).next = current_opt.take();
                }
            }

            if let Some(next) = current_opt {
                next.prev = prev_ptr;
            } else {
                self.tail = prev_ptr;
            }

            self.size -= 1;
        }
    }

    fn get(&self, index: usize) -> i32 {
        if index >= self.size {
            return -1;
        }
        let mut current = &self.head;
        for _ in 0..index {
            if let Some(node) = current {
                current = &node.next;
            }
        }
        if let Some(node) = current {
            node.value
        } else {
            -1
        }
    }

    fn print(&self) {
        print!("DoublyList (size={}): ", self.size);
        let mut current = &self.head;
        while let Some(node) = current {
            print!("{} ", node.value);
            current = &node.next;
        }
        println!();
    }

    fn save(&self, filename: &str) {
        if let Ok(mut file) = File::create(filename) {
            let _ = writeln!(file, "DOUBLY");
            let _ = writeln!(file, "{}", self.size);
            let mut current = &self.head;
            while let Some(node) = current {
                let _ = writeln!(file, "{}", node.value);
                current = &node.next;
            }
        }
    }

    fn load(&mut self, filename: &str) {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let mut lines = reader.lines();
            
            if let Some(Ok(type_line)) = lines.next() {
                if type_line == "DOUBLY" {
                    if let Some(Ok(size_line)) = lines.next() {
                        if let Ok(sz) = size_line.parse::<usize>() {
                            for _ in 0..sz {
                                if let Some(Ok(val_line)) = lines.next() {
                                    if let Ok(val) = val_line.parse::<i32>() {
                                        self.push(val);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

struct QueueNode {
    value: i32,
    next: Option<Box<QueueNode>>,
}

struct Queue {
    front: Option<Box<QueueNode>>,
    rear: *mut QueueNode,
    size: usize,
}

impl Queue {
    fn new() -> Self {
        Queue {
            front: None,
            rear: std::ptr::null_mut(),
            size: 0,
        }
    }

    fn push(&mut self, value: i32) {
        let mut node = Box::new(QueueNode { value, next: None });
        let node_ptr = &mut *node as *mut QueueNode;

        if !self.rear.is_null() {
            unsafe {
                (*self.rear).next = Some(node);
            }
        } else {
            self.front = Some(node);
        }

        self.rear = node_ptr;
        self.size += 1;
    }

    fn pop(&mut self) -> i32 {
        if let Some(node) = self.front.take() {
            self.front = node.next;
            if self.front.is_none() {
                self.rear = std::ptr::null_mut();
            }
            self.size -= 1;
            node.value
        } else {
            -1
        }
    }

    fn peek(&self) -> i32 {
        if let Some(node) = &self.front {
            node.value
        } else {
            -1
        }
    }

    fn print(&self) {
        print!("Queue (size={}): ", self.size);
        let mut current = &self.front;
        while let Some(node) = current {
            print!("{} ", node.value);
            current = &node.next;
        }
        println!();
    }

    fn save(&self, filename: &str) {
        if let Ok(mut file) = File::create(filename) {
            let _ = writeln!(file, "QUEUE");
            let _ = writeln!(file, "{}", self.size);
            let mut current = &self.front;
            while let Some(node) = current {
                let _ = writeln!(file, "{}", node.value);
                current = &node.next;
            }
        }
    }

    fn load(&mut self, filename: &str) {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let mut lines = reader.lines();
            
            if let Some(Ok(type_line)) = lines.next() {
                if type_line == "QUEUE" {
                    if let Some(Ok(size_line)) = lines.next() {
                        if let Ok(sz) = size_line.parse::<usize>() {
                            for _ in 0..sz {
                                if let Some(Ok(val_line)) = lines.next() {
                                    if let Ok(val) = val_line.parse::<i32>() {
                                        self.push(val);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

struct TreeNode {
    value: i32,
    left: Option<Box<TreeNode>>,
    right: Option<Box<TreeNode>>,
}

struct Tree {
    root: Option<Box<TreeNode>>,
    size: usize,
}

impl Tree {
    fn new() -> Self {
        Tree { root: None, size: 0 }
    }

    fn insert_helper(node: Option<Box<TreeNode>>, value: i32) -> Option<Box<TreeNode>> {
        if let Some(mut n) = node {
            if value < n.value {
                n.left = Self::insert_helper(n.left.take(), value);
            } else if value > n.value {
                n.right = Self::insert_helper(n.right.take(), value);
            }
            Some(n)
        } else {
            Some(Box::new(TreeNode {
                value,
                left: None,
                right: None,
            }))
        }
    }

    fn insert(&mut self, value: i32) {
        self.root = Self::insert_helper(self.root.take(), value);
        self.size += 1;
    }

    fn find_min(node: &Box<TreeNode>) -> i32 {
        let mut current = node;
        while let Some(left) = &current.left {
            current = left;
        }
        current.value
    }

    fn delete_helper(
        node: Option<Box<TreeNode>>,
        value: i32,
        deleted: &mut bool,
    ) -> Option<Box<TreeNode>> {
        if let Some(mut n) = node {
            if value < n.value {
                n.left = Self::delete_helper(n.left.take(), value, deleted);
                Some(n)
            } else if value > n.value {
                n.right = Self::delete_helper(n.right.take(), value, deleted);
                Some(n)
            } else {
                *deleted = true;

                if n.left.is_none() && n.right.is_none() {
                    None
                } else if n.left.is_none() {
                    n.right.take()
                } else if n.right.is_none() {
                    n.left.take()
                } else {
                    let min_val = Self::find_min(n.right.as_ref().unwrap());
                    n.value = min_val;
                    let mut temp_deleted = false;
                    n.right = Self::delete_helper(n.right.take(), min_val, &mut temp_deleted);
                    *deleted = false;
                    Some(n)
                }
            }
        } else {
            None
        }
    }

    fn del(&mut self, value: i32) {
        let mut deleted = false;
        self.root = Self::delete_helper(self.root.take(), value, &mut deleted);
        if deleted {
            self.size -= 1;
        }
    }

    fn search_helper(node: &Option<Box<TreeNode>>, value: i32) -> bool {
        if let Some(n) = node {
            if n.value == value {
                true
            } else if value < n.value {
                Self::search_helper(&n.left, value)
            } else {
                Self::search_helper(&n.right, value)
            }
        } else {
            false
        }
    }

    fn get(&self, value: i32) -> bool {
        Self::search_helper(&self.root, value)
    }

    fn get_height(node: &Option<Box<TreeNode>>) -> i32 {
        if let Some(n) = node {
            let left_height = Self::get_height(&n.left);
            let right_height = Self::get_height(&n.right);
            if left_height > right_height {
                left_height + 1
            } else {
                right_height + 1
            }
        } else {
            0
        }
    }

    fn print_level(node: &Option<Box<TreeNode>>, level: i32, indent: usize, spacing: usize) {
        if level == 1 {
            for _ in 0..indent {
                print!(" ");
            }
            if let Some(n) = node {
                print!("{}", n.value);
            } else {
                print!(" ");
            }
            for _ in 0..spacing {
                print!(" ");
            }
        } else if level > 1 {
            if let Some(n) = node {
                Self::print_level(&n.left, level - 1, indent, spacing);
                Self::print_level(&n.right, level - 1, indent, spacing);
            } else {
                Self::print_level(&None, level - 1, indent, spacing);
                Self::print_level(&None, level - 1, indent, spacing);
            }
        }
    }

    fn print(&self) {
        println!("Tree (size={}):", self.size);
        if self.root.is_none() {
            println!("Empty tree");
            return;
        }

        let height = Self::get_height(&self.root);
        let max_width = (1 << height) - 1;

        for level in 1..=height {
            let num_nodes = 1 << (level - 1);
            let spacing = (max_width / num_nodes) - 1;
            let indent = (max_width - (num_nodes + (num_nodes - 1) * spacing)) / 2;

            Self::print_level(&self.root, level, indent as usize, spacing as usize);
            println!();
        }
    }

    fn save_helper(file: &mut File, node: &Option<Box<TreeNode>>) {
        if let Some(n) = node {
            let _ = writeln!(file, "{}", n.value);
            Self::save_helper(file, &n.left);
            Self::save_helper(file, &n.right);
        }
    }

    fn save(&self, filename: &str) {
        if let Ok(mut file) = File::create(filename) {
            let _ = writeln!(file, "TREE");
            let _ = writeln!(file, "{}", self.size);
            Self::save_helper(&mut file, &self.root);
        }
    }

    fn load(&mut self, filename: &str) {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let mut lines = reader.lines();
            
            if let Some(Ok(type_line)) = lines.next() {
                if type_line == "TREE" {
                    if let Some(Ok(size_line)) = lines.next() {
                        if let Ok(sz) = size_line.parse::<usize>() {
                            for _ in 0..sz {
                                if let Some(Ok(val_line)) = lines.next() {
                                    if let Ok(val) = val_line.parse::<i32>() {
                                        self.insert(val);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

fn contains_only_digits(s: &str) -> bool {
    if s.is_empty() {
        return false;
    }
    s.chars().all(|c| c.is_ascii_digit())
}

fn main() {
    let args: Vec<String> = std::env::args().collect();

    if args.len() < 3 {
        eprintln!("Usage: program <filename> <command> [args...]");
        std::process::exit(1);
    }

    let filename = &args[1];
    let command = &args[2];

    if command != "PRINT" && args.len() >= 4 && !contains_only_digits(&args[3]) {
        eprintln!("Argument contains a non-number character");
        std::process::exit(1);
    }

    if command.starts_with('M') {
        let mut arr = Array::new();
        arr.load(filename);

        if command == "MPUSH" && args.len() >= 4 {
            if let Ok(val) = args[3].parse::<i32>() {
                arr.push(val);
                arr.save(filename);
            }
        } else if command == "MDEL" && args.len() >= 4 {
            if let Ok(idx) = args[3].parse::<usize>() {
                arr.del(idx);
                arr.save(filename);
            }
        } else if command == "MGET" && args.len() >= 4 {
            if let Ok(idx) = args[3].parse::<usize>() {
                println!("{}", arr.get(idx));
            }
        } else if command == "PRINT" {
            arr.print();
        }
    } else if command.starts_with('S') {
        let mut s = Stack::new();
        s.load(filename);

        if command == "SPUSH" && args.len() >= 4 {
            if let Ok(val) = args[3].parse::<i32>() {
                s.push(val);
                s.save(filename);
            }
        } else if command == "SPOP" {
            let value = s.pop();
            println!("{}", value);
            s.save(filename);
        } else if command == "SPEEK" {
            println!("{}", s.peek());
        } else if command == "PRINT" {
            s.print();
        }
    } else if command.starts_with('F') {
        let mut list = ForwardList::new();
        list.load(filename);

        if command == "FPUSH" && args.len() >= 4 {
            if let Ok(val) = args[3].parse::<i32>() {
                list.push(val);
                list.save(filename);
            }
        } else if command == "FDEL" && args.len() >= 4 {
            if let Ok(idx) = args[3].parse::<usize>() {
                list.del(idx);
                list.save(filename);
            }
        } else if command == "FGET" && args.len() >= 4 {
            if let Ok(idx) = args[3].parse::<usize>() {
                println!("{}", list.get(idx));
            }
        } else if command == "PRINT" {
            list.print();
        }
    } else if command.starts_with('L') {
        let mut list = DoublyList::new();
        list.load(filename);

        if command == "LPUSH" && args.len() >= 4 {
            if let Ok(val) = args[3].parse::<i32>() {
                list.push(val);
                list.save(filename);
            }
        } else if command == "LDEL" && args.len() >= 4 {
            if let Ok(idx) = args[3].parse::<usize>() {
                list.del(idx);
                list.save(filename);
            }
        } else if command == "LGET" && args.len() >= 4 {
            if let Ok(idx) = args[3].parse::<usize>() {
                println!("{}", list.get(idx));
            }
        } else if command == "PRINT" {
            list.print();
        }
    } else if command.starts_with('Q') {
        let mut q = Queue::new();
        q.load(filename);

        if command == "QPUSH" && args.len() >= 4 {
            if let Ok(val) = args[3].parse::<i32>() {
                q.push(val);
                q.save(filename);
            }
        } else if command == "QPOP" {
            let value = q.pop();
            println!("{}", value);
            q.save(filename);
        } else if command == "QPEEK" {
            println!("{}", q.peek());
        } else if command == "PRINT" {
            q.print();
        }
    } else if command.starts_with('T') {
        let mut t = Tree::new();
        t.load(filename);

        if command == "TINSERT" && args.len() >= 4 {
            if let Ok(val) = args[3].parse::<i32>() {
                t.insert(val);
                t.save(filename);
            }
        } else if command == "TDEL" && args.len() >= 4 {
            if let Ok(val) = args[3].parse::<i32>() {
                t.del(val);
                t.save(filename);
            }
        } else if command == "TGET" && args.len() >= 4 {
            if let Ok(val) = args[3].parse::<i32>() {
                if t.get(val) {
                    println!("Found");
                } else {
                    println!("Not found");
                }
            }
        } else if command == "PRINT" {
            t.print();
        }
    } else if command == "PRINT" {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let mut lines = reader.lines();

            if let Some(Ok(type_line)) = lines.next() {
                match type_line.as_str() {
                    "ARRAY" => {
                        let mut arr = Array::new();
                        arr.load(filename);
                        arr.print();
                    }
                    "STACK" => {
                        let mut s = Stack::new();
                        s.load(filename);
                        s.print();
                    }
                    "FORWARD" => {
                        let mut list = ForwardList::new();
                        list.load(filename);
                        list.print();
                    }
                    "DOUBLY" => {
                        let mut list = DoublyList::new();
                        list.load(filename);
                        list.print();
                    }
                    "QUEUE" => {
                        let mut q = Queue::new();
                        q.load(filename);
                        q.print();
                    }
                    "TREE" => {
                        let mut t = Tree::new();
                        t.load(filename);
                        t.print();
                    }
                    _ => {}
                }
            }
        }
    }
}