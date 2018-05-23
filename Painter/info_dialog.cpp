#include "info_dialog.h"

Info_dialog::Info_dialog(Bmp_image const* image) {
    setWindowTitle("Image info");
    // here may be memory leaks;
    QHBoxLayout* content = new QHBoxLayout(this);
    QVBoxLayout* labels = new QVBoxLayout(this);
    QVBoxLayout* values = new QVBoxLayout(this);

    QLabel* width = new QLabel("Width:      ", this);
    QLabel* height = new QLabel("Height:     ", this);
    QLabel* size = new QLabel("Size:          ", this);
    QLabel* bitcount = new QLabel("Bitcount: ", this);
    labels->addWidget(width);
    labels->addWidget(height);
    labels->addWidget(size);
    labels->addWidget(bitcount);

    this->width = new QLabel(QString::number(image->get_width()) + QString(" px"), this);
    this->height = new QLabel(QString::number(image->get_height()) + QString(" px"), this);
    this->size = new QLabel(Info_dialog::make_beauty(image->get_size()), this);
    this->bitcount = new QLabel(QString::number(image->get_bitcount()) + QString(" bits"), this);
    values->addWidget(this->width);
    values->addWidget(this->height);
    values->addWidget(this->size);
    values->addWidget(this->bitcount);

    content->addLayout(labels);
    content->addLayout(values);

    setLayout(content);
}

Info_dialog::~Info_dialog() {
    delete width;
    delete height;
    delete size;
    delete bitcount;
}

void Info_dialog::change_info(Bmp_image const* image) {
    width->setText(QString::number(image->get_width()) + QString(" px"));
    height->setText(QString::number(image->get_height()) + QString(" px"));
    size->setText(make_beauty(image->get_size()));
    bitcount->setText(QString::number(image->get_bitcount()) + QString(" bits"));
}

QString Info_dialog::make_beauty(int size) {
    std::vector<QString> units{" B", " Kb", " Mb", " Gb"};

    int power = round(log(size)/log(1024));
    power = std::min(power, static_cast<int>(units.size() - 1));
    double beauty_size = size / pow(1024, power);

    QString unit = units.at(power);
    return QString::number(beauty_size, 'g', 3) + unit;
}
