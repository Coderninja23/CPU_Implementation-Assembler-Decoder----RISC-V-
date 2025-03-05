#include <bits/stdc++.h>
using namespace std;

// Register class is for obtaining the binary representation of the registers in machine code
class Register
{
private:
    unordered_map<string, bitset<5>> registers;
    unordered_map<uint8_t, int> values;

public:
    Register()
    {
        registers.insert({{"x0", bitset<5>(string("00000"))},
                          {"x1", bitset<5>(string("00001"))},
                          {"x2", bitset<5>(string("00010"))},
                          {"x3", bitset<5>(string("00011"))},
                          {"x4", bitset<5>(string("00100"))},
                          {"x5", bitset<5>(string("00101"))},
                          {"x6", bitset<5>(string("00110"))},
                          {"x7", bitset<5>(string("00111"))},
                          {"x8", bitset<5>(string("01000"))},
                          {"x9", bitset<5>(string("01001"))},
                          {"x10", bitset<5>(string("01010"))},
                          {"x11", bitset<5>(string("01011"))},
                          {"x12", bitset<5>(string("01100"))},
                          {"x13", bitset<5>(string("01101"))},
                          {"x14", bitset<5>(string("01110"))},
                          {"x15", bitset<5>(string("01111"))},
                          {"x16", bitset<5>(string("10000"))},
                          {"x17", bitset<5>(string("10001"))},
                          {"x18", bitset<5>(string("10010"))},
                          {"x19", bitset<5>(string("10011"))},
                          {"x20", bitset<5>(string("10100"))},
                          {"x21", bitset<5>(string("10101"))},
                          {"x22", bitset<5>(string("10110"))},
                          {"x23", bitset<5>(string("10111"))},
                          {"x24", bitset<5>(string("11000"))},
                          {"x25", bitset<5>(string("11001"))},
                          {"x26", bitset<5>(string("11010"))},
                          {"x27", bitset<5>(string("11011"))},
                          {"x28", bitset<5>(string("11100"))},
                          {"x29", bitset<5>(string("11101"))},
                          {"x30", bitset<5>(string("11110"))},
                          {"x31", bitset<5>(string("11111"))}});
    }

    bitset<5> getResiterBits(string reg)
    {
        if (registers.find(reg) != registers.end())
        {
            return registers[reg];
        }
        return bitset<5>(string("00000"));
    }
};

// Instruction class is used to create independent objects for all the instructions. All instructions are treated as an object and their machine code is stored in the object.
class Instruction
{
private:
    unordered_map<string, string> typeOfInstruction = {
        {"ADD", "rtype"},
        {"SUB", "rtype"},
        {"SLL", "rtype"},
        {"XOR", "rtype"},
        {"SRL", "rtype"},
        {"SRA", "rtype"},
        {"OR", "rtype"},
        {"AND", "rtype"},
        {"LR.D", "rtype"},
        {"SC.D", "rtype"},
        {"SLT", "rtype"},
        {"SLTU", "rtype"},
        {"MUL", "rtype"},

        {"ADDI", "itype"},
        {"SLLI", "itype"},
        {"XORI", "itype"},
        {"SRLI", "itype"},
        {"SRAI", "itype"},
        {"ORI", "itype"},
        {"ANDI", "itype"},
        {"JALR", "itype"},

        {"JAL", "jtype"},

        {"SD", "stype"},
        {"SW", "stype"},
        {"SH", "stype"},
        {"SB", "stype"},

        {"LUI", "utype"},

        {"BEQ", "btype"},
        {"BLT", "btype"},
        {"BGE", "btype"},
        {"BNE", "btype"},
        {"BLTU", "btype"},
        {"BGEU", "btype"},
        // {"JALR", "btype"},
    };

    int hexToDec(string num)
    {
        int len = (num.length());
        int base = 1;
        int temp = 0;
        for (int i = len - 1; i >= 0; i--)
        {
            if (num[i] >= '0' && num[i] <= '9')
            {
                temp += (num[i] - 48) * base;
                base = base * 16;
            }
            else if (num[i] >= 'A' && num[i] <= 'F')
            {
                temp += (num[i] - 55) * base;
                base = base * 16;
            }
        }
        return temp;
    }

    string opcode;
    vector<string> operands;
    bitset<32> machineCode;
    Register *regi = new Register();

    int generateMachineCode()
    {
        if (typeOfInstruction.find(opcode) != typeOfInstruction.end())
        {

            string type = typeOfInstruction[opcode];
            if (type == "rtype")
            {
                rtypeInstruction();
            }
            else if (type == "itype")
            {
                itypeInstruction();
            }
            else if (type == "jtype")
            {
                jtypeInstruction();
            }
            else if (type == "stype")
            {
                stypeInstruction();
            }
            else if (type == "utype")
            {
                utypeInstruction();
            }
            else if (type == "btype")
            {
                btypeInstruction();
            }

            return 1;
        }
        else
        {
            return -1;
        }
    }

    int rtypeInstruction()
    {
        bitset<7> opcodeBits(string("0110011"));
        unordered_map<string, bitset<7>> func7 = {
            {"ADD", bitset<7>(string("0000000"))},
            {"SUB", bitset<7>(string("0100000"))},
            {"SLT", bitset<7>(string("0000000"))},
            {"SLTU", bitset<7>(string("0000000"))},
            {"SLL", bitset<7>(string("0000000"))},
            {"XOR", bitset<7>(string("0000000"))},
            {"SRL", bitset<7>(string("0000000"))},
            {"SRA", bitset<7>(string("0000000"))},
            {"OR", bitset<7>(string("0000000"))},
            {"AND", bitset<7>(string("0000000"))},
            {"LR.D", bitset<7>(string("0001000"))},
            {"SC.D", bitset<7>(string("0001100"))},
            {"MUL", bitset<7>(string("0000001"))}};

        unordered_map<string, bitset<3>> func3 = {
            {"ADD", bitset<3>(string("000"))},
            {"SUB", bitset<3>(string("000"))},
            {"SLT", bitset<3>(string("010"))},
            {"SLTU", bitset<3>(string("011"))},
            {"SLL", bitset<3>(string("001"))},
            {"XOR", bitset<3>(string("100"))},
            {"SRL", bitset<3>(string("101"))},
            {"SRA", bitset<3>(string("101"))},
            {"OR", bitset<3>(string("110"))},
            {"AND", bitset<3>(string("111"))},
            {"LR.D", bitset<3>(string("011"))},
            {"SC.D", bitset<3>(string("011"))},
            {"MUL", bitset<3>(string("000"))}};

        bitset<7> f7 = func7[opcode];
        bitset<3> f3 = func3[opcode];
        string rs2 = operands[2], rs1 = operands[1], rd = operands[0];
        bitset<5> sourceReg2 = regi->getResiterBits(rs2);
        bitset<5> souceReg1 = regi->getResiterBits(rs1);
        bitset<5> destinationRegister = regi->getResiterBits(rd);
        string encodedString = f7.to_string() + sourceReg2.to_string() + souceReg1.to_string() + f3.to_string() + destinationRegister.to_string() + opcodeBits.to_string();
        machineCode = bitset<32>(string(encodedString));
        return 1;
    }

    int itypeInstruction()
    {
        if (opcode == "JALR")
        {
            bitset<7> opcodeBits(string("1100111"));
            string rd = operands[0];
            string rs1, imm;

            int i = 0;
            for (i = 0; i < operands[1].size(); i++)
            {
                if (operands[1][i] == '(')
                    break;
                imm += operands[1][i];
            }

            i++;
            while (operands[1][i] != ')')
            {
                rs1 += operands[1][i];
                i++;
            }

            int immInt = 0;
            if (imm[0] == '0' && imm[1] == 'x')
            {
                immInt = hexToDec(imm.substr(2, imm.length() - 2));
            }
            else
            {
                immInt = stoi(imm);
            }

            bitset<3> f3(string("000"));
            bitset<5> destinationRegister = regi->getResiterBits(rd);
            bitset<5> souceReg1 = regi->getResiterBits(rs1);
            bitset<12> immediate(immInt);

            string encodedString = immediate.to_string() + souceReg1.to_string() + f3.to_string() + destinationRegister.to_string() + opcodeBits.to_string();
            machineCode = bitset<32>(encodedString);
            return 1;
        }
        bitset<7> opcodeBits(string("0010011"));

        unordered_map<string, bitset<3>> func3 = {
            {"ADDI", bitset<3>(string("000"))},
            {"SLLI", bitset<3>(string("001"))},
            {"XORI", bitset<3>(string("100"))},
            {"SRLI", bitset<3>(string("101"))},
            {"SRAI", bitset<3>(string("101"))},
            {"ORI", bitset<3>(string("110"))},
            {"ANDI", bitset<3>(string("111"))},
        };

        bitset<3> f3 = func3[opcode];
        string rs1 = operands[1], rd = operands[0], imm = operands[2];
        int immInt = 0;
        if (imm[0] == '0' && imm[1] == 'x')
        {
            immInt = hexToDec(imm.substr(2, imm.length() - 2));
        }
        else
        {
            immInt = stoi(imm);
        }
        bitset<12> immediate(immInt);
        bitset<5> souceReg1 = regi->getResiterBits(rs1);
        bitset<5> destinationRegister = regi->getResiterBits(rd);
        string encodedString = immediate.to_string() + souceReg1.to_string() + f3.to_string() + destinationRegister.to_string() + opcodeBits.to_string();
        machineCode = bitset<32>(string(encodedString));
        return 1;
    }

    int jtypeInstruction()
    {
        bitset<7> opcodeBits(string("1101111"));

        string rd = operands[0], imm = operands[1];
        int immInt = 0;
        if (imm[0] == '0' && imm[1] == 'x')
        {
            immInt = hexToDec(imm.substr(2, imm.length() - 2));
        }
        else
        {
            immInt = stoi(imm);
        }
        if (immInt & 1)
            immInt--;
        immInt = immInt >> 1;

        int twentyBit = (1 << 19) & (immInt);
        twentyBit = twentyBit >> 19;
        bitset<1> immFirst(twentyBit);

        int num = pow(2, 10) - 1;
        int oneToTenBit = num & immInt;
        bitset<10> immSecond(oneToTenBit);

        int eleventhBit = (1 << 10) & (immInt);
        eleventhBit = eleventhBit >> 10;
        bitset<1> immThird(eleventhBit);

        int tillNinteenth = pow(2, 19) - 1;
        int tillTwelve = pow(2, 11) - 1;
        int requiredRangeFourthImmediate = tillNinteenth ^ tillTwelve;
        int lastBits = immInt & requiredRangeFourthImmediate;
        lastBits = lastBits >> 11;
        bitset<8> immFourth(lastBits);

        bitset<5> destinationRegister = regi->getResiterBits(rd);

        string encodedString = immFirst.to_string() + immSecond.to_string() + immThird.to_string() + immFourth.to_string() + destinationRegister.to_string() + opcodeBits.to_string();

        machineCode = bitset<32>(string(encodedString));

        return 1;
    }

    int stypeInstruction()
    {
        bitset<7> opcodeBits(string("0100011"));

        unordered_map<string, bitset<3>> func3 = {
            {"SD", bitset<3>(string("011"))},
            {"SW", bitset<3>(string("010"))},
            {"SH", bitset<3>(string("001"))},
            {"SB", bitset<3>(string("000"))},
        };

        string rs2 = operands[0];
        string rs1, imm;

        int i = 0;
        for (i = 0; i < operands[1].size(); i++)
        {
            if (operands[1][i] == '(')
                break;
            imm += operands[1][i];
        }

        i++;
        while (operands[1][i] != ')')
        {
            rs1 += operands[1][i];
            i++;
        }

        int offset = 0;
        if (imm[0] == '0' && imm[1] == 'x')
        {
            offset = hexToDec(imm.substr(2, imm.length() - 2));
        }
        else
        {
            offset = stoi(imm);
        }

        int zeroToFour = pow(2, 4) - 1;
        int immSecond = zeroToFour & offset;

        int zeroToEleven = pow(2, 11) - 1;
        int fiveToEleven = zeroToEleven ^ zeroToFour;
        int immFirst = fiveToEleven & offset;
        immFirst = immFirst >> 5;

        bitset<5> secondImmediate(immSecond);
        bitset<7> firstImmediate(immFirst);

        bitset<5> sourceReg2 = regi->getResiterBits(rs2);
        bitset<5> souceReg1 = regi->getResiterBits(rs1);

        bitset<3> f3 = func3[opcode];
        string encodedString = firstImmediate.to_string() + sourceReg2.to_string() + souceReg1.to_string() + f3.to_string() + secondImmediate.to_string() + opcodeBits.to_string();
        machineCode = bitset<32>(string(encodedString));
        return 1;
    }

    int utypeInstruction()
    {
        bitset<7> opcodeBits(string("0110111"));

        string rd = operands[0], imm = operands[1];
        int immInt = 0;
        if (imm[0] == '0' && imm[1] == 'x')
        {
            immInt = hexToDec(imm.substr(2, imm.length() - 2));
        }
        else
        {
            immInt = stoi(imm);
        }
        bitset<20> immediate(immInt);
        bitset<5> destinationRegister = regi->getResiterBits(rd);
        string encodedString = immediate.to_string() + destinationRegister.to_string() + opcodeBits.to_string();
        machineCode = bitset<32>(string(encodedString));
        return 1;
    }

    int btypeInstruction()
    {
        bitset<7> opcodeBits(string("1100011"));

        unordered_map<string, bitset<3>> func3 = {
            {"BEQ", bitset<3>(string("000"))},
            {"BGE", bitset<3>(string("101"))},
            {"BLT", bitset<3>(string("100"))},
            {"BNE", bitset<3>(string("001"))},
            {"BLTU", bitset<3>(string("110"))},
            {"BGEU", bitset<3>(string("111"))},
            {"JALR", bitset<3>(string("000"))},
        };

        string rs1 = operands[0], rs2 = operands[1], imm = operands[2];
        int immediateValue = 0;
        if (imm[0] == '0' && imm[1] == 'x')
        {
            immediateValue = hexToDec(imm.substr(2, imm.length() - 2));
        }
        else
        {
            immediateValue = stoi(imm);
        }
        if (immediateValue & 1)
            immediateValue--;
        immediateValue = immediateValue >> 1;

        int zeroToFour = pow(2, 4) - 1;
        int oneToFour = zeroToFour ^ 1;
        int thirdImm = oneToFour & immediateValue;

        int zeroToTen = pow(2, 10) - 1;
        int fiveToTen = zeroToFour ^ zeroToTen;
        int secondImm = fiveToTen & immediateValue;
        secondImm = secondImm >> 4;

        int eleventhBit = 1 << 10;
        int fourthImm = eleventhBit & immediateValue;

        int twelvethBit = 1 << 11;
        int firstImm = twelvethBit & immediateValue;
        firstImm = firstImm >> 11;

        bitset<1> firstImmediateLocation(firstImm);
        bitset<6> secondImmediateLocation(secondImm);
        bitset<4> thirdImmediateLocation(thirdImm);
        bitset<1> fourthImmediateLocation(fourthImm);

        bitset<5> secondRegister = regi->getResiterBits(rs2);
        bitset<5> firstRegister = regi->getResiterBits(rs1);

        bitset<3> f3(func3[opcode]);

        string encodedString = firstImmediateLocation.to_string() + secondImmediateLocation.to_string() + secondRegister.to_string() + firstRegister.to_string() + f3.to_string() + thirdImmediateLocation.to_string() + fourthImmediateLocation.to_string() + opcodeBits.to_string();
        machineCode = bitset<32>(string(encodedString));
        
        return 1;
    }

public:
    Instruction(string &opcode, vector<string> &operands)
    {
        this->opcode = opcode;
        this->operands = operands;
        generateMachineCode();
    }

    bitset<32> getMachineCode()
    {
        return machineCode;
    }
};

// Assmebler class for converting assembly code into machine code.
class Assembler
{
private:
    string AssemblyCode;
    vector<bitset<32>> machineCode;

public:
    Assembler(string inputString)
    {
        this->AssemblyCode = inputString;
    }

    void Assemble()
    {
        stringstream ss(AssemblyCode);
        string instruction;

        while (getline(ss, instruction))
        {
            istringstream instructionParsing(instruction);
            string opcode;
            string operands;
            instructionParsing >> opcode;
            transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
            getline(instructionParsing, operands);
            operands.erase(remove(operands.begin(), operands.end(), ' '), operands.end());
            vector<string> operandsVector;
            stringstream operandsStream(operands);
            string ope;
            while (getline(operandsStream, ope, ','))
            {
                operandsVector.push_back(ope);
            }

            Instruction instr(opcode, operandsVector);
            machineCode.push_back(instr.getMachineCode());
        }
    }
    vector<bitset<32>> getMachineCode()
    {
        return machineCode;
    }
};

// For reading the assembly instructions from the input file.
void read_from_file(const string &fileName, ofstream &outfile, string &input)
{
    ifstream inputFile(fileName);
    string line;
    while (getline(inputFile, line))
    {
        input += line;
        input += "\n";
    }
}

int main()
{
    ofstream outfile("machine.txt");
    string input = "";
    read_from_file("assembly.txt", outfile, input);
    Assembler assemble(input);
    assemble.Assemble();
    vector<bitset<32>> machineCode = assemble.getMachineCode();

    for (auto &it : machineCode)
    {
        outfile << it << endl;
    }

    return 0;
}