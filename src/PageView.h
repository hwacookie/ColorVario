#ifndef KYSTSOFT_PAGEVIEW_H
#define KYSTSOFT_PAGEVIEW_H

#include "Signal.h"
#include <dali-toolkit/dali-toolkit.h>

namespace Kystsoft {

class PageView : public Dali::ConnectionTracker
{
public:
	PageView() {}
	PageView(const PageView& other) = delete;
	PageView& operator=(const PageView& rhs) = delete;
	operator Dali::Toolkit::ScrollView() const { return scrollView; }
	void create(const Dali::Vector2& pageSize);
	void addPage(Dali::Actor page);
	int pageCount() const { return static_cast<int>(scrollView.GetChildCount()) - 1; } // TODO: Figure out where the extra child comes from!
	int currentPageIndex() const { return currentPage; }
	int targetPageIndex() const { return targetPage; }
	void showPage(int pageIndex) { scrollTo(pageIndex); }
	const Signal<int>& currentPageChangedSignal() const { return currentPageChangedSignl; }
private:
	void scrollTo(int pageIndex);
	void onStageEntered(Dali::Actor) { scrollView.SetKeyInputFocus(); }
	void onWheelEvent(const Dali::WheelEvent& event);
	void onScrollCompleted(const Dali::Vector2& currentScrollPosition);
	float pageWidth = 0;
	Dali::Toolkit::ScrollView scrollView;
	Dali::Toolkit::RulerPtr rulerX;
	int currentPage = 0;
	int targetPage = 0;
	Signal<int> currentPageChangedSignl;
};

} // namespace Kystsoft

#endif // KYSTSOFT_PAGEVIEW_H