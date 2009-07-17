
/**
 * OpenEmulator
 * Mac OS X Inspector Panel Controller
 * (C) 2009 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls the inspector.
 */

#import "InspectorPanelController.h"
#import "Document.h"

NSString *itemIdentifiers[] = 
{
	@"Emulation",
	@"Expansions",
	@"Disk Drives",
	@"Printers and Modems",
	@"Video",
	@"Audio",
};

@implementation InspectorPanelController

- (id)init
{
	return [super initWithWindowNibName:@"InspectorPanel"];
}

- (void)windowDidLoad
{
    [super windowDidLoad];
	
	fDefaults = [NSUserDefaults standardUserDefaults];
	oldTabTag = -1;
	
	NSPanel *panel = (NSPanel *)[self window];
//	[panel setBecomesKeyOnlyIfNeeded:YES];
	[panel setFrameUsingName:@"InspectorPanel"];
	[panel setFrameAutosaveName:@"InspectorPanel"];
	
	int tabTag = [fDefaults integerForKey:@"OEInspectorPanelViewIndex"];
	[fTabMatrix selectCellWithTag:tabTag];
	[self setView:tabTag isInit:YES];
	
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(toggleInspectorPanel:)
												 name:@"toggleInspectorPanel"
											   object:nil];
	
	[self setInspectedDocument:nil];
	[NSApp addObserver:self
			forKeyPath:@"mainWindow.windowController.document"
			   options:0
			   context:[InspectorPanelController class]];
}

- (void)toggleInspectorPanel:(id)sender
{
    NSWindow *window = [self window];
    if ([window isVisible])
		[window close];
	else
		[window orderFront:nil];
}

- (BOOL)validateUserInterfaceItem:(id)item
{
    if ([item action] == @selector(toggleInspectorPanel:))
	{  
		NSString *menuTitle;
		if (![[self window] isVisible])
			menuTitle = NSLocalizedString(@"Show Inspector",
										  @"Title for menu item to show the Inspector panel"
										  "(should be the same as the initial menu item in the nib).");
		else
			menuTitle = NSLocalizedString(@"Hide Inspector",
										  @"Title for menu item to hide the Inspector panel.");
		[item setTitleWithMnemonic:menuTitle];
    }
	
    return YES;
}

- (id)inspectedDocument
{
	return inspectedDocument;
}

- (void)setInspectedDocument:(id)theDocument
{
	inspectedDocument = theDocument;
}

- (void)observeValueForKeyPath:(NSString *)keyPath
					  ofObject:(id)object
						change:(NSDictionary *)change
					   context:(void *)context
{
    if (context == [InspectorPanelController class])
		[self activeDocumentChanged];
	else
		[super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
}

- (void)activeDocumentChanged
{
    id activeDocument = [[[NSApp mainWindow] windowController] document];
    if (activeDocument == [self inspectedDocument])
		return;
	
	if ([self inspectedDocument])
		[documentController commitEditing];
	
	if (activeDocument && [activeDocument isKindOfClass:[Document class]])
		[self setInspectedDocument:activeDocument];
	else
		[self setInspectedDocument:nil];
}

/*- (void)inspectorPanelDidResignKey:(NSNotification *)notification
{
    [documentController commitEditing];
}
*/

- (NSView *)getView:(int)tabTag
{
	switch (tabTag)
	{
		case 0:
			return fEmulationView;
		case 1:
			return fExpansionsView;
		case 2:
			return fDiskDrivesView;
		case 3:
			return fPortsView;
		case 4:
			return fVideoView;
		case 5:
			return fAudioView;
	}
	
	return fEmulationView;
}

- (void)selectView:(id)sender
{
	[self setView:[fTabMatrix selectedTag] isInit:FALSE];
}

- (void)setView:(int)tabTag isInit:(bool)isInit
{
	if (tabTag == oldTabTag)
		 return;
	
	float oldHeight = 0;
	if (oldTabTag >= 0)
	{
		NSView *oldView = [self getView:oldTabTag];
		oldHeight = [oldView frame].size.height;
		
		[oldView setHidden:YES];
		[oldView removeFromSuperview];
	}
	
	NSWindow *window = [self window];
	NSRect frame = [window frame];

	NSView *view = [self getView:tabTag];
	
	float difference = ([view frame].size.height - oldHeight) *
		[window userSpaceScaleFactor];
	if (!isInit)
		frame.origin.y -= difference;
	frame.size.height += difference;
	
    [window setFrame:frame display:YES animate:YES];
	[[window contentView] addSubview:view];
    [view setHidden:NO];
    
	[window setTitle:NSLocalizedString(itemIdentifiers[tabTag], "")];
	
    [fDefaults setInteger:tabTag forKey:@"OEInspectorPanelViewIndex"];
	oldTabTag = tabTag;
}

@end
