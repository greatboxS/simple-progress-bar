#include "progressbar.h"

ProgressBar::ProgressBar(FILE *fd, double max, uint8_t percent, uint32_t width)
{
    if (max <= 0)
        return;
    double value = max * percent / 100.0;
    Init(fd, max, value, width);
}

ProgressBar::ProgressBar(FILE *fd, double max, double currentValue, uint32_t width)
{
    Init(fd, max, currentValue, width);
}

int ProgressBar::Init(FILE *fd, double max, double currentValue, uint32_t width)
{
    if (max <= 0 || !fd)
        return -1;
    m_fd = fd;
    m_maxValue = max;
    m_currentValue = currentValue;
    m_percent = (uint8_t)(100 * currentValue / max);
    m_width = width;
    m_ok = true;
    return 0;
}

int ProgressBar::SetColor(int fColor, int bColor)
{
}

bool ProgressBar::UpdatePercent(uint8_t percent)
{
}

bool ProgressBar::update(double value, int up, int down)
{
#define DRAW(...) fprintf(m_fd, __VA_VRG__)

#if defined(WIN32)

#else

#endif
}
