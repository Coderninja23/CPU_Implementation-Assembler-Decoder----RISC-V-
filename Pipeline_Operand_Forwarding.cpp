#include <bits/stdc++.h>
using namespace std;

//-------------------------------------------
// Assembler
//-------------------------------------------


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
        {"DIV", "rtype"},
        {"REM", "rtype"},

        {"ADDI", "itype"},
        {"SLLI", "itype"},
        {"XORI", "itype"},
        {"SRLI", "itype"},
        {"SRAI", "itype"},
        {"ORI", "itype"},
        {"ANDI", "itype"},
        {"JALR", "itype"},
        {"LD", "itype"},

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
            {"MUL", bitset<7>(string("0000001"))},
            {"DIV", bitset<7>(string("0000001"))},
            {"REM", bitset<7>(string("0000001"))}};

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
            {"MUL", bitset<3>(string("000"))},
            {"DIV", bitset<3>(string("100"))},
            {"REM", bitset<3>(string("110"))}};

        bitset<7> f7 = func7[opcode];
        bitset<3> f3 = func3[opcode];
        string rs2 = operands[2], rs1 = operands[1], rd = operands[0];
        bitset<5> sourceReg2 = regi->getResiterBits(rs2);
        bitset<5> souceReg1 = regi->getResiterBits(rs1);
        bitset<5> destinationRegister = regi->getResiterBits(rd);
        //Change
        if(rs2[0]!='x'){
            cout<<"Error in insturction"<<endl;
            exit(0);
        }
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
        else if(opcode=="LD"){
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

            int offset = 0;
            if (imm[0] == '0' && imm[1] == 'x')
            {
                offset = hexToDec(imm.substr(2, imm.length() - 2));
            }
            else
            {
                offset = stoi(imm);
            }

            bitset<7>opcodeBits(string("0000011"));
            bitset<3>func3(string("011"));

            bitset<12> immediate(offset);
            bitset<5> souceReg1 = regi->getResiterBits(rs1);
            bitset<5> destinationRegister = regi->getResiterBits(rd);
            string encodedString = immediate.to_string() + souceReg1.to_string() + func3.to_string() + destinationRegister.to_string() + opcodeBits.to_string();
            machineCode = bitset<32>(string(encodedString));
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
        //Change
        if(imm[0]=='x'){
            cout<<"Error in instruction"<<endl;
            exit(0);
        }
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


        int zeroToFour = pow(2, 5) - 1;
        int immSecond = zeroToFour & offset;

        int zeroToEleven = pow(2, 12) - 1;
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
        fourthImm = (fourthImm >> 10);

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

//-------------------------------------------
// Pipeline begins
//-------------------------------------------

class Instruction_memory
{
private:
    string inputString;
    vector<int> vec;

public:
    void storeInstructions(string input)
    {
        this->inputString = input;
        stringstream ss(input);
        string str;
        while (getline(ss, str))
        {
            bitset<32> binary(str);
            int val = binary.to_ulong();
            if (binary[0])
            {
                val -= (1 << 32);
            }
            vec.push_back(val);
        }
    }

    int getInstruction(int program_counter)
    {
        if (program_counter >= vec.size())
            return -1;
        return vec[program_counter];
    }
};

class Register_file
{
private:
    vector<int> register_values;

public:
    Register_file()
    {
        register_values = vector<int>(32, 0);
    }

    int change_value(int reg, int value)
    {
        if (reg >= 32 || reg < 0)
            return -1;
        // Old value
        int curr_val = register_values[reg];
        register_values[reg] = value;
        // Returning older value after updating
        return curr_val;
    }

    int get_current_value(int reg)
    {
        if (reg >= 32 || reg < 0)
            return -1;
        return register_values[reg];
    }

    void printValuesAllRegisters()
    {
        for (int i = 0; i < 32; i++)
        {
            cout << "x" << i << ":" << register_values[i] << endl;
        }
    }
};

class Program_counter
{
private:
    int pc;

public:
    Program_counter()
    {
        this->pc = 0;
    }

    int get_program_counter()
    {
        return pc;
    }

    void addOneInstruction()
    {
        pc++;
    }

    int next_instruction()
    {
        pc++;
        return pc;
    }

    void updateToLocation(int location)
    {
        pc = location;
    }

    int change_location(int lines)
    {
        pc += lines;
        return pc;
    }
};

class IFID
{
private:
    int ir;
    int npc;
    int dpc;

public:
    IFID()
    {
        this->ir = -1;
        this->npc = -1;
        this->dpc = -1;
    }

    void updateIr(int instr)
    {
        ir = instr;
    }
    int getInstr()
    {
        return ir;
    }
    void updateNpc(int npc)
    {
        this->npc = npc;
    }
    int getNpc()
    {
        return npc;
    }
    void updateDpc(int dpc)
    {
        this->dpc = dpc;
    }
    int getDpc()
    {
        return dpc;
    }
};

class IDEX
{
private:
    int jpc;
    int dpc;
    int npc;
    int imm;
    int func;
    int rdl;
    int cw;
    int rs1;
    int rs2;
    int func7;

public:
    IDEX()
    {
        this->jpc = -1;
        this->dpc = -1;
        this->npc = -1;
        this->imm = -1;
        this->func = -1;
        this->func7 = -1;
        this->rdl = -1;
        this->cw = -1;
        this->rs1 = -1;
        this->rs2 = -1;
    }

    void updateJpc(int jpc)
    {
        this->jpc = jpc;
    }
    int getJpc()
    {
        return jpc;
    }
    void updateDpc(int dpc)
    {
        this->dpc = dpc;
    }
    int getDpc()
    {
        return dpc;
    }
    void updateNpc(int npc)
    {
        this->npc = npc;
    }
    int getNpc()
    {
        return npc;
    }
    void updateImm(int imm)
    {
        this->imm = imm;
    }
    int getImm()
    {
        return imm;
    }
    void updateFunc(int func)
    {
        this->func = func;
    }
    int getFunc()
    {
        return func;
    }
    void updateFunc7(int func7)
    {
        this->func7 = func7;
    }
    int getFunc7()
    {
        return func7;
    }
    void updateRdl(int rdl)
    {
        this->rdl = rdl;
    }
    int getRdl()
    {
        return rdl;
    }
    void updateCw(int cw)
    {
        this->cw = cw;
    }
    int getCw()
    {
        return cw;
    }
    void updateRs1(int rs1)
    {
        this->rs1 = rs1;
    }
    int getRs1()
    {
        return rs1;
    }
    void updateRs2(int rs2)
    {
        this->rs2 = rs2;
    }
    int getRs2()
    {
        return rs2;
    }
};

class EXMO
{
private:
    int cw;
    int ALUOut;
    int rs2;
    int rdl;

public:
    EXMO()
    {
        this->cw = -1;
        this->ALUOut = -1;
        this->rs2 = -1;
        this->rdl = -1;
    }

    void updateCw(int cw)
    {
        this->cw = cw;
    }
    int getCw()
    {
        return cw;
    }
    void updateAluout(int ALUOut)
    {
        this->ALUOut = ALUOut;
    }
    int getALUOut()
    {
        return ALUOut;
    }
    void updateRs2(int rs2)
    {
        this->rs2 = rs2;
    }
    int getRs2()
    {
        return rs2;
    }
    void updateRdl(int rdl)
    {
        this->rdl = rdl;
    }
    int getRdl()
    {
        return rdl;
    }
};

class MOWB
{
private:
    int cw;
    int ldRes;
    int ALUOut;
    int rdl;

public:
    MOWB()
    {
        this->cw = -1;
        this->ldRes = -1;
        this->ALUOut = -1;
        this->rdl = -1;
    }

    void updateCw(int cw)
    {
        this->cw = cw;
    }
    int getCw()
    {
        return cw;
    }
    void updateAluout(int ALUOut)
    {
        this->ALUOut = ALUOut;
    }
    int getALUOut()
    {
        return ALUOut;
    }
    void updateLdRes(int ldRes)
    {
        this->ldRes = ldRes;
    }
    int getLdRes()
    {
        return ldRes;
    }
    void updateRdl(int rdl)
    {
        this->rdl = rdl;
    }
    int getRdl()
    {
        return rdl;
    }
};

class Data_memory
{
private:
    vector<int> data;

public:
    void storeData(int memoryLocation, int val)
    {
        int n = data.size();
        while (n <= memoryLocation)
        {
            data.push_back(-1);
            n = data.size();
        }
        data[memoryLocation] = val;
    }

    int getData(int memoryLocation)
    {
        int n = data.size();
        if (memoryLocation >= n)
            return -1;
        return data[memoryLocation];
    }

    void printData()
    {
        for (int i = 0; i < data.size(); i++)
        {
            cout << "Data at location " << i << ": " << data[i] << " " << endl;
        }
        cout << endl;
    }
};

class Control_Unit
{
private:
    //{51, 0} -> RType Instruction
    //{19, 1} -> IType Instruction
    //{99, 2} -> BType Instruction
    //{111, 3} -> JType Instruction
    //{55, 4} -> UType Instruction
    //{35, 5} -> SType Instruction
    unordered_map<int, int> mp;

public:
    Control_Unit()
    {
        mp[51] = 0;
        mp[19] = 1;
        mp[99] = 2;
        mp[111] = 3;
        mp[55] = 4;
        mp[35] = 5;
        mp[103] = 6;
    }

    int getALU_Src(int opcode)
    {
        if (opcode == 3)
            return 1;
        else if (mp[opcode] == 0)
            return 0;
        else if (mp[opcode] == 1)
            return 1;
        else if (mp[opcode] == 2)
            return 0;
        else if (mp[opcode] == 3)
            return 1;
        else if (mp[opcode] == 4)
            return 1;
        else if (mp[opcode] == 5)
            return 0;
        else if(mp[opcode] == 6)
            return 1;
        else
            return -1;
    }

    int getALU_Op1(int opcode)
    {
        // load
        if (opcode == 3)
            return 0;
        else if (mp[opcode] == 0)
            return 1;
        else if (mp[opcode] == 1)
            return 1;
        else if (mp[opcode] == 2)
            return 0;
        else if (mp[opcode] == 3)
            return 0;
        else if (mp[opcode] == 4)
            return 0;
        else if (mp[opcode] == 5)
            return 0;
        else if(mp[opcode] == 6)
            return 1;
        else
            return -1;
    }

    int getALU_Op0(int opcode)
    {
        if (mp[opcode] == 0)
            return 0;
        else if (mp[opcode] == 1)
            return 0;
        else if (mp[opcode] == 2)
            return 1;
        else if (mp[opcode] == 3)
            return 0;
        else if (mp[opcode] == 4)
            return 0;
        else if (mp[opcode] == 5)
            return 0;
        else if(mp[opcode] == 6)
            return 0;
        else
            return -1;
    }

    bool regRead1(int opcode)
    {
        if (mp[opcode] == 0)
            return true;
        else if (mp[opcode] == 1)
            return true;
        else if (mp[opcode] == 2)
            return true;
        else if (mp[opcode] == 3)
            return false;
        else if (mp[opcode] == 4)
            return false;
        else if (mp[opcode] == 5)
            return true;
        else if(mp[opcode] == 6){
            return true;
        }
        else
            return false;
    }
    // Branch specifies what index to branch to
    bool isBranch(int opcode)
    {
        if (mp[opcode] == 2)
            return true;
        return false;
    }

    bool isJump(int opcode)
    {
        if (mp[opcode] == 3)
            return true;
        return false;
    }

    bool memWrite(int opcode)
    {
        if (mp[opcode] == 5)
            return true;
        return false;
    }

    bool memRead(int opcode)
    {
        if (opcode == 3)
            return true;
        return false;
    }

    bool regWrite(int opcode)
    {
        // JUMP?
        if (mp[opcode] == 0 || mp[opcode] == 1)
            return true;
        return false;
    }

    bool Mem_Reg(int opcode)
    {
        if (opcode == 3)
        {
            return true;
        }
        return false;
    }

    bool canOperandForward(int opcode)
    {
        if (mp[opcode] == 0 || (mp[opcode] == 1 && opcode != 3))
            return true;
        return false;
    }

    bool isStore(int opcode)
    {
        return mp[opcode] == 5;
    }

    bool isLoad(int opcode)
    {
        return opcode == 3;
    }

    bool isJALR(int opcode){
        return mp[opcode]==6;
    }

    bool canOperandForwardMemory(int opcode)
    {
        if (mp[opcode] == 5 || opcode == 3)
            return true;
        return false;
    }

    int getALUZeroFlag(int opcode, int rs1, int rs2, int func3)
    {
        if (mp[opcode] != 2)
            return 0;
        else if (func3 == 0)
            return rs1 == rs2;
        else if (func3 == 4)
            return rs1 < rs2;
        else if (func3 == 5)
            return rs1 >= rs2;
        return -1;
    }
};
// Change
int ALUControl(int ALU_op, int func3, int func7)
{
    if (ALU_op == 0)
        return 2;
    else if (ALU_op == 1)
        return 6;
    else if (ALU_op == 2)
    {
        if (func3 == 7)
            return 0;
        else if (func3 == 6)
        {
            if (func7 == 0)
                return 1;
            else if (func7 == 1)
                return 8;
        }
        else if (func3 == 0)
        {
            if (func7 == 0)
                return 2;
            else if (func7 == 1)
                return 4;
            return 6;
        }
        else if (func3 == 4)
        {
            if (func7 == 1)
                return 5;
        }
    }
    return -1;
}
// Change
vector<int> ALU(int rs1, int rs2, int aluSelect)
{
    if (aluSelect == 0)
    {
        int res = (rs1 & rs2);
        return {res, -1};
    }
    else if (aluSelect == 1)
    {
        int res = (rs1 | rs2);
        return {res, -1};
    }
    else if (aluSelect == 2)
    {
        int res = rs1 + rs2;
        return {res, -1};
    }
    else if (aluSelect == 4)
    {
        int res = rs1 * rs2;
        return {res, -1};
    }
    else if (aluSelect == 5)
    {
        if (rs2 == 0)
            return {-1, -1};
        int res = rs1 / rs2;
        return {res, -1};
    }
    else if (aluSelect == 6)
    {
        int res = rs1 - rs2;
        return {res, -1};
    }
    else if (aluSelect == 8)
    {
        if (rs2 == 0)
            return {-1, -1};
        int res = rs1 % rs2;
        return {res, -1};
    }
    else
        return {-1, -1};
}

class Pipeline
{
private:
    string input;
    Program_counter pc;
    IFID ifid;
    IDEX idex;
    EXMO exmo;
    MOWB mowb;
    Data_memory dm;
    Register_file regfile;
    Instruction_memory IM;
    Control_Unit cw;

    void clearIFID()
    {
        ifid.updateDpc(-1);
        ifid.updateIr(-1);
        ifid.updateNpc(-1);
    }

    void clearIDEX()
    {
        idex.updateCw(-1);
        idex.updateDpc(-1);
        idex.updateFunc(-1);
        idex.updateFunc7(-1);
        idex.updateImm(-1);
        idex.updateJpc(-1);
        idex.updateNpc(-1);
        idex.updateRdl(-1);
        idex.updateRs1(-1);
        idex.updateRs2(-1);
    }

    void clearEXMO()
    {
        exmo.updateAluout(-1);
        exmo.updateCw(-1);
        exmo.updateRdl(-1);
        exmo.updateRs2(-1);
    }

    int InstructionFetch()
    {
        int instr = IM.getInstruction(pc.get_program_counter());
        if (instr == -1)
            return -1;
        ifid.updateIr(instr);
        int dpc = pc.get_program_counter();
        ifid.updateDpc(dpc);
        int npc = pc.get_program_counter() + 1;
        ifid.updateNpc(npc);
        pc.addOneInstruction();
        return 1;
    }

    int InstructionDecode()
    {
        int npc = ifid.getNpc();
        if (npc == -1)
            return -1;
        idex.updateNpc(npc);

        int ir = ifid.getInstr();
        int allOn = INT_MAX;
        int tillEleven = pow(2, 12) - 1;
        int twelveOnwards = (allOn ^ tillEleven);

        // IDEX.JPC=IFID.NPC +
        // SignedExtend(IFID.IR[31-12])
        // IDEX.DPC = IFID.DPC
        int result = (twelveOnwards & ir);
        result = (result >> 12);
        result /= 4;
        int jpc = (npc + result);
        idex.updateJpc(jpc);
        idex.updateDpc(ifid.getDpc());

        // IDEX.CW = controller(IFID.IR[6-0])
        int tillSix = pow(2, 7) - 1;
        result = (ir & tillSix);
        idex.updateCw(result);

        int func7 = (ir >> 25) & 0x7F;
        if (idex.getCw() == 19)
            func7 = 0;
        idex.updateFunc7(func7);

        // IDEX.rdl = IFID.IR[11-7]
        int sevenToEleven = (tillSix ^ tillEleven);
        result = (ir & sevenToEleven);
        result = (result >> 7);
        idex.updateRdl(result);

        // IDEX.imm = IFID.IR[31-20]
        int tillNineteen = pow(2, 20) - 1;
        int twentyOnwards = (tillNineteen ^ allOn);
        if (!cw.isStore(idex.getCw()) && !cw.isBranch(idex.getCw()) && !cw.isJump(idex.getCw()))
        {
            int immediate = (ir >> 20) & 0xFFF;

            if (immediate & 0x800) { 
                immediate |= 0xFFFFF000; 
            }
            idex.updateImm(immediate);
        }
        else if (cw.isBranch(idex.getCw()))
        {
            int32_t imm_12 = (ir >> 31) & 0x1;   
            int32_t imm_11 = (ir >> 7) & 0x1;  
            int32_t imm_10_5 = (ir >> 25) & 0x3F;
            int32_t imm_4_1 = (ir >> 8) & 0xF; // Bits 11-8

            int32_t immediate = (imm_12 << 12) | (imm_11 << 11) | (imm_10_5 << 5) | (imm_4_1 << 1);

            if (imm_12)
            {
                immediate |= (~0x1FFF);
            }

            bitset<32> machine(immediate);
            idex.updateImm(immediate);
        }
        //Addition
        else if(cw.isJump(idex.getCw())){
            int32_t imm20 = (ir >> 31) & 0x1;      
            int32_t imm10_1 = (ir >> 21) & 0x3FF;  
            int32_t imm11 = (ir >> 20) & 0x1;      
            int32_t imm19_12 = (ir >> 12) & 0xFF;  

            int32_t immediate = (imm20 << 20) | (imm19_12 << 12) | (imm11 << 11) | (imm10_1 << 1);

            if (imm20 == 1) {
                immediate |= 0xFFF00000; 
            }
            idex.updateImm(immediate);
            idex.updateJpc(immediate);
        }
        else
        {
            int imm_lower = (ir >> 7) & 0x1F; 
            int imm_upper = (ir >> 25) & 0x7F; 

            int imm = (imm_upper << 5) | imm_lower;

            if (imm & 0x800)
            {                  
                imm |= 0xFFFFF000;
            }
            idex.updateImm(imm);
        }
        
        // IDEX.func = IFID.IR[14-12]
        int tillfourteen = pow(2, 15) - 1;
        int twelveToFourteen = (tillfourteen ^ tillEleven);
        result = (ir & twelveToFourteen);
        result = (result >> 12);
        idex.updateFunc(result);

        // IDEX.rs1 = GPR[IFID.IR[19-15]]
        // Operand forwarding. Receive data from exmo register if the dest(reg-exmo)==rsl1
        int fifteenToNineteen = (tillNineteen ^ tillfourteen);
        result = (fifteenToNineteen & ir);
        result = (result >> 15); 
        if (exmo.getRdl() == result && !cw.isBranch(exmo.getCw()) && !cw.isStore(exmo.getCw()) && result!=0)
        {
            // The next instruction-R-type/I-type
            if (!cw.isLoad(exmo.getCw()))
            {

                if (cw.canOperandForward(exmo.getCw()))
                {
                    idex.updateRs1(exmo.getALUOut());
                }
                else
                {
                    // Stall
                }
            }

            else
            {
                idex.updateRs1(dm.getData(exmo.getALUOut()));
            }
        }
        else if (mowb.getRdl() == result && !cw.isBranch(mowb.getCw()) && !cw.isStore(exmo.getCw()) && result!=0)
        {
            if (!cw.isLoad(exmo.getCw()))
            {
                if (cw.canOperandForward(mowb.getCw()))
                {
                    idex.updateRs1(mowb.getALUOut());
                }
                else
                {
                    // stall
                }
            }
            else
            {
                idex.updateRs1(mowb.getLdRes());
            }
        }
        else
        {
            idex.updateRs1(regfile.get_current_value(result));
        }
        if (cw.regRead1(idex.getCw()))
        {
            if (!cw.getALU_Src(idex.getCw()))
            {
                // Checking for operand forwarding in rs2.
                int tillTwentyFour = pow(2, 25) - 1;
                int twentyToTwentyFour = (tillTwentyFour ^ tillNineteen);
                result = (ir & twentyToTwentyFour);
                result = (result >> 20); // rsl2
                if (exmo.getRdl() == result && !cw.isBranch(exmo.getCw()) && idex.getCw()!=19 && result!=0)
                {
                    if (!cw.isLoad(exmo.getCw()))
                    {

                        if (cw.canOperandForward(exmo.getCw()))
                        {
                            idex.updateRs2(exmo.getALUOut());
                        }
                        else
                        {
                            // stall
                        }
                    }
                    else
                    {
                        idex.updateRs2(dm.getData(exmo.getALUOut()));
                    }
                }
                else if (mowb.getRdl() == result && !cw.isBranch(mowb.getCw()) && idex.getCw()!=19 && result!=0)
                {
                    if (!cw.isLoad(exmo.getCw()))
                    {
                        if (cw.canOperandForward(mowb.getCw()))
                        {
                            idex.updateRs2(mowb.getALUOut());
                        }
                        else
                        {
                            // stall
                        }
                    }
                    else
                    {
                        idex.updateRs2(mowb.getLdRes());
                    }
                }
                else
                {
                    idex.updateRs2(regfile.get_current_value(result));
                }
            }
            else
            {
                result = (ir & twentyOnwards);
                result = (result >> 20);
                idex.updateRs2(result);
            }
        }
        ifid.updateDpc(-1);
        ifid.updateIr(-1);
        ifid.updateNpc(-1);
        return 1;
    }

    int InstructionExecute()
    {
        int opcode = idex.getCw();
        if (opcode == -1)
            return -1;
        int imm = idex.getImm();
        int func = idex.getFunc();

        int func7 = idex.getFunc7();
        int ALUOp1 = cw.getALU_Op1(opcode);
        int ALUOp0 = cw.getALU_Op0(opcode);
        int ALUOp = 2 * ALUOp1 + ALUOp0;
        int ALUSelect = ALUControl(ALUOp, func, func7);
        if(opcode==103)ALUSelect=2;


        // EXMO.ALUOUT = ALU(ALUSelect, IDEX.rs1, IDEX.rs2)
        // ALUZeroFlag = (IDEX.rs1 == IDEX.rs2)
        int rs1 = idex.getRs1();
        int rs2 = idex.getRs2();
        if (cw.isStore(opcode))
        {
            rs2 = idex.getImm();
        }
        vector<int> ALUOutput = ALU(rs1, rs2, ALUSelect);
        int ALURes = ALUOutput[0];
        int ALUZeroFlag = cw.getALUZeroFlag(opcode, rs1, rs2, idex.getFunc());
        exmo.updateAluout(ALURes);
        exmo.updateCw(idex.getCw());
        if (cw.isBranch(opcode) && ALUZeroFlag)
        {
            int newPC = pc.get_program_counter() + idex.getImm() / 4 - 2;
            pc.updateToLocation(newPC);
            clearIFID();
            clearIDEX();
            clearEXMO();
            return 1;
        }

        if (cw.isJump(opcode))
        {
            regfile.change_value(idex.getRdl(), pc.get_program_counter()-1);
            pc.updateToLocation(idex.getJpc()/4+pc.get_program_counter()-2);
            clearIFID();
            clearIDEX();
            clearEXMO();
            return 1;
        }

        if(cw.isJALR(opcode)){
            regfile.change_value(idex.getRdl(), pc.get_program_counter());
            pc.updateToLocation(idex.getImm());
            clearIFID();
            clearIDEX();
            clearEXMO();
            return 1;
        }

        exmo.updateRs2(idex.getRs2());
        exmo.updateRdl(idex.getRdl());
        clearIDEX();
        return 1;
    }

    int MemoryAccess()
    {
        int opcode = exmo.getCw();
        if (opcode == -1)
            return -1;
        // If EXMO.CW.MemWrite Then
        //     DM[EXMO.ALUOUT] = IDEX.rs2
        if (cw.memWrite(opcode))
        {
            // dm.storeData()
            dm.storeData(exmo.getALUOut()/4, exmo.getRs2());
        }
        // If EXMO.CW.MemRead Then
        //      MOWB.LDOUT = DM[EXMO.ALUOUT]
        if (cw.memRead(opcode))
        {
            mowb.updateLdRes(dm.getData(exmo.getALUOut()/4));
        }

        // MOWB.ALUOUT = EXMO.ALUOUT
        // MOWB.CW = EXMO.CW
        mowb.updateAluout(exmo.getALUOut());
        mowb.updateCw(exmo.getCw());
        mowb.updateRdl(exmo.getRdl());

        exmo.updateAluout(-1);
        exmo.updateCw(-1);
        exmo.updateRdl(-1);
        exmo.updateRs2(-1);

        return 1;
    }

    int RegisterWrite()
    {
        int opcode = mowb.getCw();
        if (opcode == -1)
            return -1;

        // If MOWB.CW.RegWrite Then
        if (cw.regWrite(opcode))
        {
            //If MOWB.CW.Mem2Reg
            if (cw.Mem_Reg(opcode))
            {
            //Then GPR[MOWB.rdl] = MOWB.LDOUT
                regfile.change_value(mowb.getRdl(), mowb.getLdRes());
            }
            //Else GPR[MOWB.rdl] = MOWB.ALUOUT
            else
            {
                regfile.change_value(mowb.getRdl(), mowb.getALUOut());
            }
        }
        mowb.updateAluout(-1);
        mowb.updateCw(-1);
        mowb.updateLdRes(-1);
        mowb.updateRdl(-1);
        return -1;
    }

    bool empty()
    {
        if (ifid.getDpc() != -1)
            return false;
        else if (ifid.getInstr() != -1)
            return false;
        else if (ifid.getNpc() != -1)
            return false;
        else if (idex.getCw() != -1)
            return false;
        else if (idex.getDpc() != -1)
            return false;
        else if (idex.getFunc() != -1)
            return false;
        else if (idex.getImm() != -1)
            return false;
        else if (idex.getJpc() != -1)
            return false;
        else if (idex.getNpc() != -1)
            return false;
        else if (idex.getRdl() != -1)
            return false;
        else if (idex.getRs1() != -1)
            return false;
        else if (idex.getFunc7() != -1)
            return false;
        else if (idex.getRs2() != -1)
            return false;
        else if (exmo.getALUOut() != -1)
            return false;
        else if (exmo.getCw() != -1)
            return false;
        else if (exmo.getRdl() != -1)
            return false;
        else if (exmo.getRs2() != -1)
            return false;
        else if (mowb.getALUOut() != -1)
            return false;
        else if (mowb.getCw() != -1)
            return false;
        else if (mowb.getLdRes() != -1)
            return false;
        else if (mowb.getRdl() != -1)
            return false;
        else
            return true;
    }

public:
    Pipeline(string inputString)
    {
        pc = Program_counter();
        ifid = IFID();
        idex = IDEX();
        exmo = EXMO();
        mowb = MOWB();
        dm = Data_memory();
        regfile = Register_file();
        cw = Control_Unit();
        IM.storeInstructions(inputString);
    }

    void execute()
    {
        int cnt = 0;
        while (1)
        {
            cnt++;
            RegisterWrite();
            MemoryAccess();
            InstructionExecute();
            InstructionDecode();
            InstructionFetch();
            if (empty())
                break;
        }
        cout<<"\nNumber of cycles: "<<cnt<<endl;
    }

    void printRegisterValues()
    {
        regfile.printValuesAllRegisters();
    }

    void printMemory()
    {
        dm.printData();
    }
};

string generateInputFromBitset(vector<bitset<32>> &machineCode)
{
    string res = "";
    for (auto &it : machineCode)
    {
        res += it.to_string() + "\n";
    }
    return res;
}

int main()
{
    ofstream outfile("machine.txt");
    string input = "";
    read_from_file("assemblyCode.txt", outfile, input);
    Assembler assemble(input);
    assemble.Assemble();
    vector<bitset<32>> machineCode = assemble.getMachineCode();

    string inputString = generateInputFromBitset(machineCode);

    Pipeline pipe = Pipeline(inputString);

    pipe.execute();
    pipe.printRegisterValues();
    pipe.printMemory();

    return 0;
}