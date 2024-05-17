// #include "asm_sort/bubble_sort.h"
// #include "asm_sort/quick_sort.h"
#include "c_sort/bubble_sort.h"
#include "c_sort/insertion_sort.h"
#include "c_sort/selection_sort.h"
#include "c_sort/quick_sort.h"

#include <thread>

#include "sort_jobs.hpp"

// Settings for sorter
constexpr size_t N_FLOOR   = 100;      // Min number of elements
constexpr size_t N_CEILING = 10000;    // Max number of elements
constexpr size_t DEFAULT_WORKERS = 4;  // Number of worker threads

struct SortDescriptor
{
    // This will be our API - all sort functions should acceept two arguments:
    //  1) pointer to a 32 bit signed integer
    //  2) and length of the array a size_t value.
    typedef void (*Sorter)(int32_t* arr, size_t size);

    Sorter sorter;
    const char* name;
};


struct SpeedTestResult
{
    struct Run
    {
        enum class State
        {
            NotStarted,
            Running,
            Complete
        };

        explicit Run(size_t N_in)
            : N(N_in)
            , elapsedUs(0)
            , state(State::NotStarted)
        {}

        size_t N;
        uint64_t elapsedUs;
        State state;
    };

    const char* name = nullptr;
    std::vector<Run> runs;
};



std::vector<SpeedTestResult> allocateResutSlots(
    const std::vector<SortDescriptor>& descriptors,
    const size_t min,
    const size_t max)
{
    std::vector<SpeedTestResult> resultSlots;

    for (const SortDescriptor& alg : descriptors)
    {
        resultSlots.push_back({ alg.name, {}});
        std::vector<SpeedTestResult::Run>& runs = resultSlots.back().runs;

        for (size_t n = min; n <= max; n *= 10)
        {
            runs.emplace_back(n);
        }
    }

    return resultSlots;
}


bool isFinished(const std::vector<SpeedTestResult>& resultTable,
        std::mutex& resultsAccessMutex)
{
    bool workComplete = true;
    std::lock_guard<std::mutex> guard(resultsAccessMutex);

    for (const SpeedTestResult& result : resultTable)
    {
        for (const SpeedTestResult::Run& run : result.runs)
        {
            workComplete &= run.state == SpeedTestResult::Run::State::Complete;
        }
    }

    return workComplete;
}


char randChar(char low, char high) {
    return low + rand() % (high - low + 1);
}


void draw_table(const std::vector<SpeedTestResult>& results, bool redraw)
{
    constexpr size_t TIME_WIDTH = 13;   // Width for printing time

    // for better formating, figure out the text width
    size_t maxTitleLen = 0;
    for (const SpeedTestResult& desc : results)
    {
        if (strlen(desc.name) > maxTitleLen)
        {
            maxTitleLen = strlen(desc.name);
        }
    }

    if (redraw)
    {
        // 0. move cursor to the begginning of the table, so that we (!) redraw the table
        const size_t tableHeight = results.size() + 1;
        std::cout << vt100::move_up(tableHeight);
    }

    // render table header
    std::cout << std::setw(maxTitleLen) << "N";
    for (const auto& run : results[0].runs)
    {
        std::cout << std::setw(TIME_WIDTH) << run.N;
    }
    std::cout << "\n";

    // render table body
    for (const SpeedTestResult& result : results)
    {
        std::cout << std::setw(maxTitleLen) << result.name;

        for (const SpeedTestResult::Run& run : result.runs)
        {
            std::cout << std::setw(TIME_WIDTH);
            switch (run.state)
            {
                case SpeedTestResult::Run::State::NotStarted:
                {
                    std::cout << '.';
                    break;
                }
                case SpeedTestResult::Run::State::Running:
                {
                    std::cout << randChar('A', 'z');
                    break;
                }
                case SpeedTestResult::Run::State::Complete:
                {
                    std::cout << run.elapsedUs;
                    break;
                }
                default:
                    assert(false && "invalid state");
            }
        }

        std::cout << "\n";
    }
}


/**
 * @desc runs the functor and retuns elapsed time in misroseconds [us]
 */
template<typename TUnit = std::chrono::microseconds, typename F>
uint64_t measure(F functor)
{
    using namespace std::chrono;
    uint64_t start = duration_cast<TUnit>
        (steady_clock::now().time_since_epoch()).count();

    functor();

    uint64_t end = duration_cast<TUnit>
        (steady_clock::now().time_since_epoch()).count();

    return end - start;
}


int main(int /*argc*/, char* /*argv*/[])
{
    // define what algorithms to run
    std::vector<SortDescriptor> algorithms {
        // {asm_bubble_sort,       "asm Bubble sort"},
        // {c_bubble_sort,         "C Bubble sort"},
         {c_bubble_sort_end,     "C Bubble sort end"},
         {c_bubble_sort_swap,    "C Bubble sort swap"},
        // {c_shaker_sort,         "C Shaker sort"},
        // {c_insertion_sort1,     "C Insert1 sort"},
        // {c_insertion_sort2,     "C Insert2 sort"},
        // {c_selection_sort,      "C Select sort"},
        // {c_cocktail_sort,       "C Cocktail sort"},
        {native_qsort,              "std Quick sort"},
        // {asm_quick_sort_ludvig,     "asm Quick sort - Ludvig"},
        // {asm_quick_sort_alex,       "asm Quick sort - Alex"},
        {c_quick_sort,              "C Quick sort"}
    };

    std::vector<SpeedTestResult> results = allocateResutSlots(algorithms, N_FLOOR, N_CEILING);

    // prepare tasks
    std::vector<std::function<void(void)>> tasks;

    for (size_t i = 0; i < algorithms.size(); i++)
    {
        const SortDescriptor& algorithm = algorithms[i];
        SpeedTestResult& series = results[i];

        std::vector<SpeedTestResult::Run>& runs = series.runs;

        for (SpeedTestResult::Run& run : runs)
        {
            // NOTE (ask Buck): no mutex needed because results are committed to pre-allocated
            // indepedent memory slots. But will ever see the final data?

            tasks.push_back([&run, sort = algorithm.sorter]()
                {
                    // prerun
                    run.state = SpeedTestResult::Run::State::Running;

                    // Act
                    using namespace std::chrono;

                    // generate array of random numbers.
                    std::vector<int32_t> arr = generateRandomArray(run.N);
                    assert(arr.size() == run.N);

                    auto job = [&sort, &arr]() {
                        sort(arr.data(), arr.size());
                    };
                    run.elapsedUs = measure<std::chrono::microseconds>(job);

                    // post run
                    run.state = SpeedTestResult::Run::State::Complete;
                });
        }
    }

    std::vector<std::thread> workers;
    std::mutex ticket_pool_mutex;   // regulates access to the result table

    size_t no_workers = std::thread::hardware_concurrency();
    if (no_workers == 0)
    {
        no_workers = DEFAULT_WORKERS;
    }

    for (size_t i = 0; i < no_workers; i++)
    {
        workers.emplace_back(worker_routine, std::ref(tasks), &ticket_pool_mutex);
    }

    bool redraw = false;
    do
    {
        draw_table(results, redraw);
        redraw = true;

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
    } while (!isFinished(results, ticket_pool_mutex));
    draw_table(results, true);

    for (std::thread& t : workers)
    {
        t.join();
    }

    return 0;
}
