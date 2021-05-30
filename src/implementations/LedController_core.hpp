#include "LedController.hpp"

template <size_t columns, size_t rows>
sakurajin::LedController<columns,rows>::~LedController() noexcept {
    initilized = false;
}

template <size_t columns, size_t rows>
sakurajin::LedController<columns,rows>::LedController() noexcept {};

template <size_t columns, size_t rows>
sakurajin::LedController<columns,rows>::LedController(unsigned int csPin) noexcept {
    init(csPin);
};

template <size_t columns, size_t rows>
sakurajin::LedController<columns,rows>::LedController(unsigned int dataPin, unsigned int clkPin,
        unsigned int csPin, bool useHardwareSpiParam) noexcept {
    init(dataPin, clkPin, csPin, useHardwareSpiParam);
}

template <size_t columns, size_t rows>
sakurajin::LedController<columns,rows>::LedController(const sakurajin::controller_configuration<columns,rows> &config) noexcept {
    init(config);
};

template <size_t columns, size_t rows>
sakurajin::LedController<columns,rows>::LedController(const sakurajin::LedController<columns,rows> &other) noexcept {
    if (!other.initilized) {
        return;
    }

    init(other.conf);

    for (unsigned int i = 0; i < conf.SegmentCount(); i++) {
        for (unsigned int j = 0; i < 8; i++) {
            LedStates[i][j] = other.LedStates[i][j];
        }
    }

    for (unsigned int j = 0; j < rows*columns*2; j++) {
        spidata[j] = other.spidata[j];
    }

    refreshSegments();
}

template <size_t columns, size_t rows>
void sakurajin::LedController<columns,rows>::init(unsigned int csPin) noexcept {
    sakurajin::controller_configuration<columns,rows> config;

    config.SPI_CS = csPin;
    config.useHardwareSpi = true;

    return init(config);
}

template <size_t columns, size_t rows>
void sakurajin::LedController<columns,rows>::init(unsigned int dataPin, unsigned int clkPin,
        unsigned int csPin, bool useHardwareSpiParam) noexcept {
    if (initilized) {
        return;
    }

    sakurajin::controller_configuration<columns,rows> config;

    config.SPI_MOSI = dataPin;
    config.SPI_CLK = clkPin;
    config.SPI_CS = csPin;
    config.useHardwareSpi = useHardwareSpiParam;

    init(config);
}

template <size_t columns, size_t rows>
void sakurajin::LedController<columns,rows>::init(const sakurajin::controller_configuration<columns,rows> &configuration) noexcept {
    if (initilized) {
        return;
    }

    if (!configuration.isValid()) {
        return;
    }
    conf = configuration;

    initConf();
    initSPI();

    if(!SPI_handler.isValid()){return;}

    initilized = true;
    refreshSegments();
}

template <size_t columns, size_t rows>
void sakurajin::LedController<columns,rows>::initConf() noexcept {
    resetBuffers();
}

template <size_t columns, size_t rows>
void sakurajin::LedController<columns,rows>::initSPI() noexcept {

    sakurajin::SPIconfiguration spi_conf{};
    spi_conf.MOSI = conf.SPI_MOSI;
    spi_conf.SCLK = conf.SPI_CLK;
    spi_conf.useHardwareSPI = conf.useHardwareSpi;
    spi_conf.transferSpeed = conf.spiTransferSpeed;

    SPI_handler = sakurajin::SPIconfiguration{spi_conf};

    if(conf.virtual_multi_row) {
        SPI_handler.initSSPin(conf.SPI_CS);
    } else {
        for(unsigned int i = 0; i < rows; i++) {
            SPI_handler.initSSPin(conf.row_SPI_CS[i]);
        }
    }

}

template <size_t columns, size_t rows>
bool sakurajin::LedController<columns,rows>::isInitilized() noexcept {
    return initilized;
}

// to be remvoed for version 2.2.0
template <size_t columns, size_t rows>
void sakurajin::LedController<columns,rows>::getSegmentData(unsigned int column, unsigned int row_num, sakurajin::ByteBlock* resultLocation) noexcept {
    getSegmentData(conf.getSegmentNumber(column,row_num),resultLocation);
}

// to be removed for version 2.2.0
template <size_t columns, size_t rows>
void sakurajin::LedController<columns,rows>::getSegmentData(unsigned int segmentindex,
        sakurajin::ByteBlock *resultLocation) noexcept {
    if (!initilized || segmentindex >= conf.SegmentCount() ||
            resultLocation == nullptr) {
        return;
    }

    *resultLocation = getSegmentData(segmentindex);
}

template <size_t columns, size_t rows>
sakurajin::ByteBlock sakurajin::LedController<columns,rows>::getSegmentData(unsigned int segmentindex) noexcept {
    if (!initilized || segmentindex >= conf.SegmentCount()) {
        return sakurajin::ByteBlock();
    };
    return LedStates[segmentindex];
}

template <size_t columns, size_t rows>
sakurajin::ByteBlock sakurajin::LedController<columns,rows>::getSegmentData(unsigned int column, unsigned int row_num) noexcept {
    return getSegmentData(conf.getSegmentNumber(column,row_num));
}

template <size_t columns, size_t rows>
unsigned int sakurajin::LedController<columns,rows>::getSegmentCount() noexcept {
    return columns*rows;
}

template <size_t columns, size_t rows>
const sakurajin::controller_configuration<columns,rows>& sakurajin::LedController<columns,rows>::getConfig() noexcept {
    return conf;
}
