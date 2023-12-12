#include <iostream>
#include <vector>
#include <string>

using namespace std;

using vi = vector<int>;
using vs = vector<string>;

struct marco {
    int para_num = -1;
    string name;
    vi used_paras_id;
    vs str_seg;

    string marco_out(vs arg_list) {
        string res;
        if (para_num > 0) {
            for (size_t i = 0; i < str_seg.size(); ++i) {
                res += str_seg[i];
                if (i < used_paras_id.size()) {
                    res += arg_list[used_paras_id[i]];
                }
            }
        } else {
            res += str_seg[0];
        }
        return res;
    };
};

enum type {
    DEFINE,
    UNDEF,
    EXPAND
};

vector<marco> ms;

inline string trim(string in) {
    size_t start = in.find_first_not_of(" \t\n\r");
    size_t end = in.find_last_not_of(" \t\n\r");
    if (start == string::npos || end == string::npos) {
        return "";
    }
    return in.substr(start, end - start + 1);
}

vs get_args(string argList) {
    argList = argList.substr(1, argList.size() - 2);
    int par_num = 0;
    int last_coma = -1;
    vs args;
    for (int i = 0; i < argList.size(); ++i) {
        char ch = argList[i];
        if (ch == '(') {
            ++par_num;
        }
        if (ch == ')') {
            --par_num;
        }
        if (ch == ',' and par_num == 0) {
            args.push_back(trim(argList.substr(last_coma + 1, i - (last_coma + 1))));
            last_coma = i;
        }
    }
    string last = trim(argList.substr(last_coma + 1, argList.size() - (last_coma + 1)));
    if (last != "") {
        args.push_back(last);
    }
    return args;
}

bool def_basic(string def_str, string targ_str) {
    for (const marco &m: ms) {
        if (m.para_num == 0 and m.name == def_str) {
            return false;
        }
    }

    marco new_m;
    new_m.name = def_str;
    new_m.para_num = 0;
    new_m.str_seg.push_back(targ_str);
    ms.push_back(new_m);

    return true;
}

bool def_fun(string name, string paralist, string tar_str) {
    vs paras = get_args(paralist);
    for (const marco &m: ms) {
        if (name == m.name and m.para_num == paras.size()) {
            return false;
        }
    }

    marco new_m;
    new_m.name = name;
    new_m.para_num = paras.size();

    int start = 0, end = -1, len = 0;
    int tar_size = (int) tar_str.size();
    bool con = false;
    for (size_t i = 0; i < tar_size; ++i) {
        char ch = tar_str[i];
        if (isalpha(ch) or isdigit(ch) or ch == '_') {
            if (!con) {
                start = i;
                con = true;
            }
            ++len;
        } else {
            if (con) {
                string para_name = tar_str.substr(start, len);
                bool hav_para = false;
                for (int para_id = 0; para_id < paras.size(); ++para_id) {
                    if (paras[para_id] == para_name) {
                        new_m.str_seg.push_back(tar_str.substr(end + 1, start - (end + 1)));
                        new_m.used_paras_id.push_back(para_id);
                        hav_para = true;
                        break;
                    }
                }
                if (hav_para) {
                    end = i - 1;
                }
                len = 0;
                con = false;
            }
        }
    }
    if (con) {
        string para_name = tar_str.substr(start, len);
        bool hav_para = false;
        for (int para_id = 0; para_id < paras.size(); ++para_id) {
            if (paras[para_id] == para_name) {
                new_m.str_seg.push_back(tar_str.substr(end + 1, start - (end + 1)));
                new_m.used_paras_id.push_back(para_id);
                hav_para = true;
                break;
            }
        }
        if (!hav_para) {
            new_m.str_seg.push_back(tar_str.substr(end + 1, tar_size - (end + 1)));
        }
    } else {
        new_m.str_seg.push_back(tar_str.substr(end + 1, tar_size - (end + 1)));
    }
    ms.push_back(new_m);

    return true;
}

bool undef_marco(string name_in, int num_in) {
    for (size_t i = 0; i < ms.size(); ++i) {
        marco &m = ms[i];
        if (m.name == name_in and m.para_num == num_in) {
            ms.erase(ms.begin() + i);
            return true;
        }
    }
    return false;
}

string expand(string in) {
    in += " ";
    bool con = false;
    string res = "";
    int sz = in.size();
    int start = 0, len = 0;
    for (int i = 0; i < sz; ++i) {
        char ch = in[i];
        if (isalpha(ch) or isdigit(ch) or ch == '_') {
            if (!con) {
                start = i;
                con = true;
            }
            ++len;
        } else {
            if (con) {
                string func_name = in.substr(start, len);
                if (ch == '(') {
                    int pa_num = 0;
                    int cur;
                    for (cur = i; cur < sz; ++cur) {
                        if (in[cur] == '(') {
                            ++pa_num;
                        } else if (in[cur] == ')') {
                            --pa_num;
                        }
                        if (pa_num == 0) {
                            break;
                        }
                    }

                    string argList = in.substr(i, cur - i + 1);
                    vs args = get_args(argList);
                    int arg_num = args.size();

                    bool have_func = false;
                    for (marco &m: ms) {
                        if (m.name == func_name and m.para_num == arg_num) {
                            res += m.marco_out(args);
                            have_func = true;
                            break;
                        }
                    }
                    if (!have_func) {
                        res += func_name;
                        res += in.substr(i, cur - i + 1);
                    }
                    i = cur;
                } else if (ch == ' ') {
                    bool have_marco = false;
                    for (marco &m: ms) {
                        if (m.name == func_name and m.para_num == 0) {
                            res += m.str_seg[0];
                            have_marco = true;
                            break;
                        }
                    }

                    if (!have_marco) {
                        res += func_name;
                        res += " ";
                    }
                } else {
                    res += func_name;
                    res += ch;
                }
                con = false;
                len = 0;
            } else {
                res += ch;
            }
        }
    }
    return res;
}


bool parser(string in, type type) {
    in.erase(in.find_last_not_of(" \t") + 1);
    switch (type) {
        case DEFINE: {
            string def = in.substr(7);
            def.erase(0, def.find_first_not_of(" \t"));

            string name, paralist;
            bool res;
            for (size_t i = 0; i < def.size(); ++i) {
                char ch = def[i];
                if (isalpha(ch) or isdigit(ch) or ch == '_') {
                    continue;
                } else {
                    name = def.substr(0, i);
                    def.erase(0, i);
                    if (ch != '(') {
                        def.erase(0, def.find_first_not_of(" \t"));
                        res = def_basic(name, def);
                        break;
                    } else {
                        int end_para = def.find_first_of(')');
                        paralist = def.substr(0, end_para + 1);
                        string tar = def.substr(end_para + 1);
                        res = def_fun(name, paralist, tar);
                        break;
                    }
                }
            }
            if (!res) {
                cout << "ERROR DUP" << endl;
                return false;
            }
            break;
        }

        case UNDEF: {
            string undef = in.substr(7);
            undef.erase(0, undef.find_first_not_of(" \t"));

            string name;
            int para_num;
            size_t pos = undef.find('(');
            if (pos != string::npos) {
                name = undef.substr(0, pos);
                para_num = get_args(undef.substr(pos, undef.size() - pos)).size();
            } else {
                name = undef;
                para_num = 0;
            }
            bool res = undef_marco(name, para_num);
            if (!res) {
                cout << "ERROR NFOUND" << endl;
                return false;
            }
            break;
        }

        case EXPAND: {
            cout << expand(in) << endl;
            break;
        }
        default: {

        }
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    string input;
    string stream;
    vector<marco> ss;
    while (getline(cin, input)) {
        for (size_t i = 0; i < input.size(); ++i) {
            char ch = input[i];
            if (ch <= 32 or ch == 127) {
                input[i] = ' ';
            }
        }
        bool res = true;
        if (input.compare(0, 1, "#") == 0) {
            if (stream != "") {
                parser(stream, EXPAND);
            }
            stream = "";
            if (input.compare(0, 7, "#define") == 0) {
                res = parser(input, DEFINE);
            } else if (input.compare(0, 6, "#undef") == 0) {
                res = parser(input, UNDEF);
            }

        } else {
            stream += input;
            stream += " ";
        }
        if (!res) {
            return 0;
        }
    }
    if (stream != "") {
        parser(stream, EXPAND);
    }

    return 0;
}
