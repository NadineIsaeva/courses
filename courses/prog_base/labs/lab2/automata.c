int run(int moves[], int movesLen, int res[], int resLen)
{
    enum command {PUSH, POP, CONTINUE, REPEAT, BREAK, NOT_PERMITTED};
    struct myStruct
    {
        enum command comm;
        int state;
    } tabl[4][4];
    int elements[4] = {5,9,14,104};
    int push[4][4];
    tabl[0][0].comm = PUSH; tabl[0][0].state = 1; push[0][0] = 9;
    tabl[0][1].comm = BREAK; tabl[0][1].state = 0;
    tabl[0][2].comm = PUSH; tabl[0][2].state = 2; push[0][2] = 7;
    tabl[0][3].comm = PUSH; tabl[0][3].state = 3; push[0][3] = 5;
    tabl[1][0].comm = PUSH; tabl[1][0].state = 2; push[1][0] = 3;
    tabl[1][1].comm = NOT_PERMITTED; tabl[1][1].state = 0;
    tabl[1][2].comm = PUSH; tabl[1][2].state = 2; push[1][2] = 1;
    tabl[1][3].comm = POP; tabl[1][3].state = 0;
    tabl[2][0].comm = REPEAT; tabl[2][0].state = 0;
    tabl[2][1].comm = BREAK; tabl[2][1].state = 0;
    tabl[2][2].comm = CONTINUE; tabl[2][2].state = 0;
    tabl[2][3].comm = NOT_PERMITTED; tabl[2][3].state = 0;
    tabl[3][0].comm = PUSH; tabl[3][0].state = 0; push[3][0] = 19;
    tabl[3][1].comm = POP; tabl[3][1].state = 0;
    tabl[3][2].comm = NOT_PERMITTED; tabl[3][2].state = 0;
    tabl[3][3].comm = PUSH; tabl[3][3].state = 1; push[3][3] = 14;

    int i = 0;
    int st = 0;
    int number = 0;

        while (i < movesLen)
            {
            int k = -1;
            if (moves[i] == elements[0])
                {
                    k = 0;
                }
            else if (moves[i] == elements[1])
                {
                    k = 1;
                }
        else if (moves[i] == elements[2])
                {
                    k = 2;
                }
        else if (moves[i]==elements[3])
                {
                    k = 3;
                }
        if (k == -1)
            {
                break;
            }
                struct myStruct r = tabl[st][k];
        int x = push[st][k];
        if (r.comm == POP)
            {
                if (number == 0)
                    {
                        break;
                    }
                else
                    {
                        number--;
                    }
                i++;
            }
        else if (r.comm == BREAK || r.comm == NOT_PERMITTED)
            {
                break;
            }
        else if (r.comm == CONTINUE)
            {
                    i++;
            }
        else if (r.comm == PUSH)
            {
                res[number] = x;
                number++;
                if (number == resLen)
                    {
                        break;
                    }
                i++;
            }
                st = r.state;
            }
int j;
for(j = number; j < resLen; j++)
        {
            res[j] = 0;
        }
return number;
}
