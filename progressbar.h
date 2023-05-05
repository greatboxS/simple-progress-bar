#ifndef __PROGRESSBAR_H__
#define __PROGRESSBAR_H__

#include <iostream>

#define DEFAULT_PROG_BAR_WIDTH 30U

class ProgressBar
{
private:
    double m_maxValue;
    double m_currentValue;
    uint8_t m_percent;
    uint32_t m_width;
    bool m_ok;
    FILE *m_fd;

    bool update(double value, int up, int down);
    bool isOk() { return m_ok; }

public:
    ProgressBar() : m_fd(NULL),
                    m_maxValue(0),
                    m_currentValue(0),
                    m_percent(0),
                    m_width(0),
                    m_ok(false)
    {
    }
    ProgressBar(FILE *fd, double max, uint8_t percent, uint32_t width = DEFAULT_PROG_BAR_WIDTH);
    ProgressBar(FILE *fd, double max, double currentValue, uint32_t width = DEFAULT_PROG_BAR_WIDTH);
    ~ProgressBar() {}

    int Init(FILE *fd, double max, double currentValue, uint32_t width);
    int SetColor(int fColor, int bColor);
    bool UpdatePercent(uint8_t percent);
};

#endif // __PROGRESSBAR_H__