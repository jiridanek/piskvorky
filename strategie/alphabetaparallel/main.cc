#include <iostream>

#include <csignal>
#include <ctime>
#include <cerrno>
#include <cstdio>

#include "board/cboard.h"
#include "load.h"
#include "minimax.h"
#include "func.h"
#include "minimax.cpp"
#include "alphabeta/calphabetaparallel.h"

using std::cout;
using std::cerr;
using std::endl;

void print_results();
CBoard *starting_board;

void timer_expired(int signo, siginfo_t * siginfo, void * ucontext) {
    print_results();
    exit(0);
    return;
}

void print_results() {
    CAlphaBetaParallel *ab = CAlphaBetaParallel::Get();
    char other = get_other_player(ab->GetPlayer());
    struct SMove highest_m = ab->GetBestMove();
//    int highest = ab->GetBestScore();
//    cerr << highest << " " << highest_m.m_x << " " << highest_m.m_y << endl;

    cout << other << endl;
    CBoard(*starting_board, highest_m).Print();
}

int main() {

    const int signal_number = SIGRTMIN+0;

    sigset_t empty_mask;
    sigemptyset(&empty_mask);

    struct sigaction act;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = timer_expired;
    act.sa_restorer = NULL;
    act.sa_mask = empty_mask;

    if(sigaction(signal_number, &act, NULL) != 0) {
        perror("rozbilo se sigaction");
        return -1;
    }

    sigval value;
    value.sival_int = 0;
    sigevent_t sigevent;
    sigevent.sigev_notify = SIGEV_SIGNAL;
    sigevent.sigev_signo = signal_number;
    sigevent.sigev_value = value;

    timer_t timerid;
    if(timer_create(CLOCK_MONOTONIC, &sigevent, &timerid) != 0) {
        perror("rozbilo se timer_create");
        return -1;
    }

    struct itimerspec time;
    time.it_value.tv_sec = 2;
    time.it_value.tv_nsec = 500L*1000000;
    time.it_interval.tv_sec = time.it_value.tv_sec;
    time.it_interval.tv_nsec = time.it_value.tv_nsec;
    if (timer_settime(timerid, 0, &time, NULL) != 0) {
        perror("timer_settime");
        return -1;
    }

    //timer_delete(timerid);

    char hrac;
    CBoard board(20, 20, load_board(&hrac));

    //another copy
    starting_board = new CBoard(board);

//    int depth = 5;
//    char other = get_other_player(hrac);

   // cout << evaluate(board, hrac) << endl;
   // cout << evaluate(board, other) << endl;

//    CMoveGenerator mg = board.CreateMoveGenerator(hrac);
//    struct SMove m = mg.GetNextMove();
//    int highest = minimax(other, board, depth);
//    struct SMove highest_m = m;
//    while (m.Initialized()) {
//        //CBoard candidate_board(board, m);
//        board.ApplyMove(m);
//        int new_value = minimax(other, board, depth);
//        if (new_value > highest) {
//            highest = new_value;
//            highest_m = m;
//        }
//        board.UndoMove(m);
//        m = mg.GetNextMove();
//    }
    CAlphaBetaParallel *ab = CAlphaBetaParallel::New(board, 2, signal_number);
    ab->StartProcessing(hrac);


    sigset_t sigset;
    sigemptyset(&sigset);
    while (true) {
        sigsuspend(&sigset);
    }

    return 0;
}
