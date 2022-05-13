
#include <tuple>
#include <array>
#include <ranges>
#include <optional>


#define FMT_HEADER_ONLY
#include "../fmt/core.h"
#include "../fmt/ranges.h"
#include "../fmt/args.h"

#define let const auto

using std::make_tuple;
using std::tuple;
using std::optional;
using std::array;
constexpr auto SIZE = 6561;


using tuple_u32_x4 = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;
using option_tuple = std::optional<tuple_u32_x4>;
using array_option = std::array<option_tuple, 6561Ui64>;



constexpr auto make_array() {
    array<optional<tuple<uint8_t, uint8_t, uint8_t, uint8_t>>, SIZE> arr{  };
    constexpr size_t DIGITS = 9;

    size_t n{ 0 };

    for (size_t h = 1; h <= DIGITS; h++) {
        for (size_t s = 1; s <= DIGITS; s++) {
            for (size_t d = 1; d <= DIGITS; d++) {
                for (size_t e = 1; e <= DIGITS; e++) {
                    arr[n] = make_tuple(h, s, d, e);

                    n += 1;
                }
            }
        }
    }



    return arr;

}



uint8_t play_bulls_cows(tuple_u32_x4 const r, tuple_u32_x4 const l) {
    uint8_t bulls{ 0ui8 };
    uint8_t cows{ 0ui8 };


    if (std::get<0>(r) == std::get<0>(l)) {
        bulls += 1;
    }
    if (std::get<1>(r) == std::get<1>(l)) {
        bulls += 1;
    }
    if (std::get<2>(r) == std::get<2>(l)) {
        bulls += 1;
    }
    if (std::get<3>(r) == std::get<3>(l)) {
        bulls += 1;
    }

    if ((std::get<0>(r) != std::get<0>(l)) &&
        (std::get<0>(r) == std::get<1>(l) ||
            std::get<0>(r) == std::get<2>(l) ||
            std::get<0>(r) == std::get<3>(l))) {
        cows += 1;
    }
    if (std::get<1>(r) != std::get<1>(l) &&
        (std::get<1>(r) == std::get<0>(l) ||
            std::get<1>(r) == std::get<2>(l) ||
            std::get<1>(r) == std::get<3>(l))) {
        cows += 1;
    }
    if (std::get<2>(r) != std::get<2>(l) &&
        (std::get<2>(r) == std::get<1>(l) ||
            std::get<2>(r) == std::get<0>(l) ||
            std::get<2>(r) == std::get<3>(l))) {
        cows += 1;
    }
    if (std::get<3>(r) != std::get<3>(l) &&
        (std::get<3>(r) == std::get<0>(l) ||
            std::get<3>(r) == std::get<1>(l) ||
            std::get<3>(r) == std::get<2>(l))) {
        cows += 1;
    }


    return bulls * 10 + cows;

}


auto chosen_number_gen(array_option const& guesses) {
    //array<array<uint32_t, 15>, SIZE> table{ 0 };
    uint32_t table[SIZE][15]{ 0 };

    for (size_t i = 0; i < guesses.size(); i++) {
        if (guesses[i].has_value()) {
            for (let& l : guesses) {
                if (l.has_value()) {
                    let bul_cow = play_bulls_cows(guesses[i].value(), l.value());
                    //printf("this ve %d\n", i );
                    switch (bul_cow) {
                        case 0: { table[i][0] += 1; }break;
                        case 1: { table[i][1] += 1; }break;
                        case 2: { table[i][2] += 1; }break;
                        case 3: { table[i][3] += 1; }break;
                        case 4: { table[i][4] += 1; }break;
                        case 10: { table[i][5] += 1; }break;
                        case 11: { table[i][6] += 1; }break;
                        case 12: { table[i][7] += 1; }break;
                        case 13: { table[i][8] += 1; }break;
                        case 20: { table[i][9] += 1; }break;
                        case 21: { table[i][10] += 1; }break;
                        case 22: { table[i][11] += 1; }break;
                        case 31: { table[i][12] += 1; }break;
                        case 30: { table[i][13] += 1; }break;
                        case 40: { table[i][14] += 1; }break;
                        default: break;
                    }
                }
            }
        }
    }

    uint32_t max = -1;
    auto n_index{ 0 };
    for (size_t i = 0; i < SIZE; i++) {
        let new_max = std::ranges::max(table[i]);
        if (guesses.at(i).has_value() and new_max < max) {
            max = new_max;
            n_index = i;
        }
    }

    fmt::print("n_index {}\n", n_index);

    return guesses[n_index];

}


void compare_numbers(bool& run, tuple_u32_x4 guess, tuple_u32_x4 secret,
    array_option& guesses) {
    array<bool, 15> witch{ true };

    let bulls_cows = play_bulls_cows(guess, secret);


    switch (bulls_cows) {
        case 0:
        {
            witch[0] = false;
            fmt::print("0 0\n");
        }break;
        case 1:
        {
            witch[1] = false;
            fmt::print("0 1\n");
        }break;
        case 2:
        {
            witch[2] = false;
            fmt::print("0 2\n");
        }break;
        case 3:
        {
            witch[3] = false;
            fmt::print("0 3\n");
        }break;
        case 4:
        {
            witch[4] = false;
            fmt::print("0 4\n");
        }break;
        case 10:
        {
            witch[5] = false;
            fmt::print("1 0\n");
        }break;
        case 11:
        {
            witch[6] = false;
            fmt::print("1 1\n");
        }break;
        case 12:
        {
            witch[7] = false;
            fmt::print("1 2\n");
        }break;
        case 13:
        {
            witch[8] = false;
            fmt::print("1 3\n");
        }break;
        case 20:
        {
            witch[9] = false;
            fmt::print("2 0\n");
        }break;
        case 21:
        {
            witch[10] = false;
            fmt::print("2 1\n");
        }break;
        case 22:
        {
            witch[11] = false;
            fmt::print("2 2\n");
        }break;
        case 31:
        {
            witch[12] = false;
            fmt::print("3 1\n");
        }break;
        case 30:
        {
            witch[13] = false;
            fmt::print("3 0\n");
        }break;
        case 40:
        {
            witch[14] = false;
            fmt::print("4 0\n");
            run = false;
        }break;
        default: break;
    }

    for (auto& gu : guesses) {
        if (gu.has_value()) {

            let bulls_cows2 = play_bulls_cows(guess, gu.value());

            switch (bulls_cows2) {
                case 0: { if (witch[0]) gu = {}; }break;
                case 1: { if (witch[1]) gu = {}; }break;
                case 2: { if (witch[2]) gu = {}; }break;
                case 3: { if (witch[3]) gu = {}; }break;
                case 4: { if (witch[4]) gu = {}; }break;
                case 10: { if (witch[5]) gu = {}; }break;
                case 11: { if (witch[6]) gu = {}; }break;
                case 12: { if (witch[7]) gu = {}; }break;
                case 13: { if (witch[8]) gu = {}; }break;
                case 20: { if (witch[9]) gu = {}; }break;
                case 21: { if (witch[10]) gu = {}; }break;
                case 22: { if (witch[11]) gu = {}; }break;
                case 31: { if (witch[12]) gu = {}; }break;
                case 30: { if (witch[13]) gu = {}; }break;
                case 40: { if (witch[14]) gu = {}; }break;
                default: break;
            }
        }
    }

}

size_t found_answare(bool& run, array_option& guesses) {
    auto n{ 0 };
    auto index{ 0 };

    for (size_t i = 0; i < guesses.size(); i++) {
        if (guesses[i].has_value()) {
            n +=1;
            index = i;
            if (n > 1) {
                return i;
            }
        }
    }

    if (n == 1) {
        run = false;
    }

    return index;
}


int main() {
    let secret{ make_tuple(1ui8, 2ui8, 3ui8, 4ui8) };

    fmt::print("secret {} \n", secret);

    auto guesses = make_array();


    size_t answare_index{ 0 };
    option_tuple chosen_number{};

    auto run{ true };
    while (run) {
        fmt::print("---------------------\n");
        chosen_number = chosen_number_gen(guesses);
        fmt::print("\nchosen_number {}\n", chosen_number.value());
        compare_numbers(run, chosen_number.value(), secret, guesses);
        fmt::print("\n");

        answare_index = found_answare(run, guesses);
    }


    fmt::print("Secret: {}", secret);
    fmt::print("answare {}", guesses[answare_index].value());
    fmt::print("chosen_number {}\n", chosen_number.value());





    //for (auto& i : guesses) {
    //    fmt::print("arr {}\n", i.value_or(make_tuple(0, 0, 0, 0)));
    //    //fmt::print("arr {}\n", i.value();
    //}


}

