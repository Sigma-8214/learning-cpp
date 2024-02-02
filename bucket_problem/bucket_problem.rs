use std::collections::VecDeque;

const BUCKET_SIZE_A: u32 = 3;
const BUCKET_SIZE_B: u32 = 5;
const TARGET: u32 = 4;

#[derive(Clone, Copy, Debug)]
enum Action {
    FillA,
    FillB,
    EmptyA,
    EmptyB,
    PourA,
    PourB,
}

#[derive(Clone, Default)]
struct State {
    history: Vec<Action>,
    a: u32,
    b: u32,
}

impl State {
    fn modify(mut self, action: Action) -> Self {
        self.history.push(action);
        match action {
            Action::FillA => self.a = BUCKET_SIZE_A,
            Action::FillB => self.b = BUCKET_SIZE_B,
            Action::EmptyA => self.a = 0,
            Action::EmptyB => self.b = 0,
            Action::PourA => {
                let pour = self.a.min(BUCKET_SIZE_B - self.b);
                self.a -= pour;
                self.b += pour;
            }
            Action::PourB => {
                let pour = self.b.min(BUCKET_SIZE_A - self.a);
                self.b -= pour;
                self.a += pour;
            }
        }

        self
    }
}

fn main() {
    let mut queue = VecDeque::<State>::new();
    queue.push_back(Default::default());

    while let Some(state) = queue.pop_front() {
        if state.a == TARGET || state.b == TARGET {
            println!("[*] Solution:");
            let mut sim = <State as Default>::default();
            for step in state.history {
                sim = sim.modify(step);
                println!(" |  {:?}\t({}, {})", step, sim.a, sim.b);
            }
            break;
        }

        for action in [
            Action::FillA,
            Action::FillB,
            Action::EmptyA,
            Action::EmptyB,
            Action::PourA,
            Action::PourB,
        ] {
            queue.push_back(state.clone().modify(action));
        }
    }
}
