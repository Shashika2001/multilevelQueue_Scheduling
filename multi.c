#include<stdio.h>
#include<stdlib.h>

#define Max_Processes 100

int size=0;
typedef struct process{
    int P_ID;
    int priority;
    int burst_time;
    int remaining_time;
}Process;

//enqueue function
void enqueue(Process *q,int *size,Process p){
    q[*size]=p;
    (*size)++;
}

//dequeue function
Process dequeue(Process *q,int *size){
    Process temp=q[0];
    (*size)--;
    for(int i=0;i<(*size);i++){
        q[i]=q[i++];
    }return temp;
}

//roundrobin function
void RoundRobin(Process *q,int *size,int quantum,int shift_time){
    while(shift_time!=0 && *size>0){
        if(shift_time>=quantum){
            Process exe=dequeue(q,size);
            if(exe.remaining_time>=quantum){
                shift_time=shift_time-quantum;
                exe.remaining_time=exe.remaining_time-quantum;
                if(exe.remaining_time==0){
                    printf("Process %d is executing and completed\n",exe.P_ID);

                }else{
                    enqueue(q,size,exe);
                    printf("process %d is executing %d time\n",exe.P_ID,quantum);
                }
            }else{
                shift_time=shift_time-exe.remaining_time;
                exe.remaining_time=0;
                printf("Process %d is executing and completed\n",exe.P_ID);
            }
        }else{
            if(q[0].remaining_time<=shift_time){
                shift_time=shift_time-q[0].remaining_time;
                q[0].remaining_time=0;
                dequeue(q,size);
                printf("Process %d is executing and completed\n",q[0].P_ID);
            }else{
                q[0].remaining_time=q[0].remaining_time-shift_time;
                printf("Process %d is executing %d time\n",q[0].P_ID);
                shift_time=0;

            }
        }
    }
}
//Shortest job First Function
void ShortestJobFirst(Process *q,int *size,int shift_time){
    while(shift_time!=0 && *size>0){
        int ShortestJob_ID=0;
        for(int i=1;i<*size;i++){
            if(q[i].remaining_time<q[ShortestJob_ID].remaining_time){
                ShortestJob_ID=i;
            }
        }
        Process exe=dequeue(q+ShortestJob_ID,size);
        if(exe.remaining_time>=shift_time){
            exe.remaining_time=exe.remaining_time-shift_time;
            shift_time=0;
            if(exe.remaining_time==0){
                printf("Process %d is executing and completed\n",exe.P_ID);

            }else{
                enqueue(q,size,exe);
            }
        }else{
            shift_time=shift_time-exe.remaining_time;
            exe.remaining_time=0;
            printf("Process %d is executing and completed\n",exe.P_ID);
        }

    }

}
//First In First Out Function
void FirstInFirstOut(Process *q,int *size,int shift_time){
    while(shift_time!=0 && *size>0){
        if(q[0].remaining_time>shift_time){
            q[0].remaining_time=q[0].remaining_time-shift_time;
            shift_time=0;

        }else{
            shift_time=shift_time-q[0].remaining_time;
            q[0].remaining_time=0;
            printf("Process %d is executing and completed\n", q[0].P_ID);
            dequeue(q,size);
        }
    }
}//main Function
int main(){

    Process q0[Max_Processes], q1[Max_Processes], q2[Max_Processes], q3[Max_Processes];
    int sizeq0 = 0, sizeq1 = 0, sizeq2 = 0, sizeq3 = 0;

    int num_processes,quantum,shift_time=20;
    printf("Input the Total number of Processes: ");
    scanf("%d",&num_processes);


    for(int i=1;i<=num_processes;i++){
        Process new_process;
        new_process.P_ID=i;
        printf("Input burst time: ");
        scanf("%d",&new_process.burst_time);
        printf("Input priority(0-3): ");
        scanf("%d",&new_process.priority);
        new_process.remaining_time=new_process.burst_time;

        switch(new_process.priority){
            case 0:
                enqueue(q0,&sizeq0,new_process);
                break;
            case 1:
                enqueue(q1,&sizeq1,new_process);
                break;
            case 2:
                enqueue(q2,&sizeq2,new_process);
                break;
            case 3:
                enqueue(q3,&sizeq3,new_process);
                break;
        }

    }

    printf("Input time quantum for round Robin queue: ");
    scanf("%d",&quantum);

    while(sizeq0>0 || sizeq1>0 || sizeq2>0 || sizeq3>0){
        if(sizeq0>0){
            RoundRobin(q0,&sizeq0,quantum,shift_time);
        }
        if(sizeq1>0){
            ShortestJobFirst(q1,&sizeq1,shift_time);
        }
        if(sizeq2>0){
            ShortestJobFirst(q2,&sizeq2,shift_time);
        }
        if(sizeq3>0){
            FirstInFirstOut(q3,&sizeq3,shift_time);
        }

    }
}
